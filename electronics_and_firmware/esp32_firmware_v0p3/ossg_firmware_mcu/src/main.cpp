//Open Source Smart Glasses main firmware - Wearable Intelligence System thin client
//OSSG repo: https://github.com/CaydenPierce/OpenSourceSmartGlasses
//Wearable Intelligence System Repo: https://github.com/emexlabs/WearableIntelligenceSystem
//OSSG firmware authors: Cayden Pierce, Alex Israelov

#include "../include/ossg_constants.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_event.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/message_buffer.h"
#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"

//wifi and websocket communications
#include "wifi_websocket_comms.hpp"

// JSON parsing
#include "json_parse.hpp"

//audio
#include "microphones.hpp"

static const char *TAG = "MAIN_OSSG";

MessageBufferHandle_t websocketSendBuffer;
const size_t websocketSendBufferLen = (1024 * 4 * sizeof(char *)) + sizeof(size_t); // room for websocket buffer, room for one size_t for MessageBuffer overhead

#define MEM_MSG 0

#define ENABLEDISPLAY 1

#if ENABLEDISPLAY
    #include "displaymanager.hpp"
#endif

#include <iostream>
using std::cout;
using std::endl;

void printPerfInfo(){
    printf( "Task Name\tStatus\tPrio\tHWM\tTask\tAffinity\n");
    char stats_buffer[1024];
    vTaskList(stats_buffer);
    printf("%s\n", stats_buffer);

    printf("Free Heap Size: %d", xPortGetFreeHeapSize());
}

MessageBufferHandle_t eventsBuffer;
const size_t eventsBufferLen = (1024 * 1 * sizeof(char *)) + sizeof(size_t); // room for events buffer, room for one size_t for MessageBuffer overhead
MessageTypes messageTypesList;
void eventDistributor(void *args){
    messageTypesList = MessageTypes();
    char * jsonString = (char *)malloc(eventsBufferLen);
    while (true)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));

        int bytes_written = xMessageBufferReceive(eventsBuffer, jsonString, eventsBufferLen, portMAX_DELAY);

        if (bytes_written != 0){
            JsonMessageParser jsonMessageParser = JsonMessageParser(jsonString);
            char * messageType = jsonMessageParser.getMessageType();
            ESP_LOGI(TAG, "Message Type is: %s", messageType);
            //can't use a switch statement here, so big if-else
            if (!strcmp(messageType, messageTypesList.FINAL_TRANSCRIPT)){
                ESP_LOGI(TAG, "GOT FINAL TRANSCRIPT");
            } else if (!strcmp(messageType, messageTypesList.INTERMEDIATE_TRANSCRIPT)){
                ESP_LOGI(TAG, "GOT INTERMEDIATE TRANSCRIPT");
            } else if (!strcmp(messageType, messageTypesList.SEARCH_ENGINE_RESULT)){
                ESP_LOGI(TAG, "GOT SEARCH ENGINE RESULT");
                JsonMessageParser searchEngineResultData = JsonMessageParser(jsonMessageParser.getJsonKey(messageTypesList.SEARCH_ENGINE_RESULT_DATA));
                char * title = searchEngineResultData.getJsonKey(messageTypesList.SEARCH_ENGINE_RESULT_DATA_TITLE);
                char * body = searchEngineResultData.getJsonKey(messageTypesList.SEARCH_ENGINE_RESULT_DATA_BODY);
                char * image = searchEngineResultData.getJsonKey(messageTypesList.SEARCH_ENGINE_RESULT_DATA_IMAGE);
                ESP_LOGI(TAG, "title: %s \n body: %s \n image: %s", title, body, image);
                //call display reference card here with title, body, image arguments
                displaySearchEngineResult(title, body, image);
                
                printPerfInfo();
            }
        }
    }
    free(jsonString);
}

void startTheDisplay(){
    #if ENABLEDISPLAY
        displayStart();
        displayEnterVoiceCommandStep2();
    #endif
}

extern "C"
{
    void app_main();
}
void app_main(void)
{
    int maxHeap = esp_get_free_heap_size();
    ESP_LOGI(TAG, "Free heap before NVS : %d", heap_caps_get_free_size(MALLOC_CAP_8BIT));
    esp_err_t ret;

    // NVS flash uses ~3000 bytes
    // Initialize NVS.
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // create event loop
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    //start the display
    startTheDisplay();

    // start WIFI
    wifi_init_sta();
 
    //setup eventsDistributor and eventsBuffer, which handles incoming data from WIS and calls functions based on what WIS tells us to do
    eventsBuffer = xMessageBufferCreate(eventsBufferLen);
    TaskHandle_t eventsTask = NULL;
    xTaskCreate(eventDistributor, "events_distribution_task", 6*1024, NULL, 1, &eventsTask);

    //connect to WIS web socket
    websocketSendBuffer = xMessageBufferCreate(websocketSendBufferLen);
    websocket_app_start(websocketSendBuffer, websocketSendBufferLen, eventsBuffer);

    //start websocket sending listening loop
    TaskHandle_t webSocketSendTask = NULL;
    if(BaseType_t retr = xTaskCreate(websocket_send_loop, "web_socket_send_task", 6*1024, NULL, 1, &webSocketSendTask) != pdPASS)
        ESP_LOGI(TAG, "Create Task websocket_send_loop failed, ERR: %d", retr);
    else ESP_LOGI(TAG, "Create Task websocket_send_loop SUCCESS, RES: %d", retr);

    //start websocket pinger
    TaskHandle_t webSocketPingTask = NULL;
    if(BaseType_t retr = xTaskCreate(ping_loop_task, "ping_loop_task", 2*1024, NULL, 1, &webSocketPingTask) != pdPASS)
        ESP_LOGI(TAG, "Create Task ping_loop_task failed, ERR: %d", retr);
    else ESP_LOGI(TAG, "Create Task ping_loop_task SUCCESS, RES: %d", retr);

    //audio 
    setup_audio_buffer(); //must call this before starting the audio tasks
    
    //send audio task
    TaskHandle_t sendAudioTaskHandle = NULL;
    if(BaseType_t retr = xTaskCreate(sendAudioChunk, "send_audio_chunk_task", 6*1024, websocketSendBuffer, 25, &sendAudioTaskHandle) != pdPASS)
        ESP_LOGI(TAG, "Create Task sendAudioChunk failed, ERR: %d\nFree Heap Size: %d, WANTED TO ALLOCATE %d", retr,heap_caps_get_largest_free_block(MALLOC_CAP_8BIT), 6*1024);
    else ESP_LOGI(TAG, "Create Task sendAudioChunk SUCCESS, RES: %d", retr);

    //start microphone input AFTER STARTING AUDIO QUEUE
    TaskHandle_t microphoneTaskHandle = NULL;
    if(BaseType_t retr = xTaskCreate(microphone_stream, "microphone_stream_task", 6*1024, NULL, 25, &microphoneTaskHandle) != pdPASS)
        ESP_LOGI(TAG, "Create Task microphone_stream failed, ERR: %d\nFree Heap Size: %d, WANTED TO ALLOCATE %d", retr,heap_caps_get_largest_free_block(MALLOC_CAP_8BIT), 6*1024);
    else ESP_LOGI(TAG, "Create Task microphone_stream SUCCESS, RES: %d", retr);

    return;
}