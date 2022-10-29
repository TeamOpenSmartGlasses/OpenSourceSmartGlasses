//Open Source Smart Glasses main firmware
//Authors: Cayden Pierce, Alex Israelov

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

//audio
#include "microphones.hpp"
MessageBufferHandle_t websocketSendBuffer;
const size_t websocketSendBufferLen = (1024 * 4 * sizeof(char *)) + sizeof(size_t); // room for websocket buffer, room for one size_t for MessageBuffer overhead

static const char *TAG = "MAIN_OSSG";

#define MEM_MSG 0

#define ENABLEDISPLAY 0
#if ENABLEDISPLAY
    #include "displaymanager.hpp"
#endif

#include <iostream>
using std::cout;
using std::endl;

void startTheDisplay();

void startTheDisplay(){
    #if ENABLEDISPLAY
        displayStart();
        displayCardSearchTextonlyDemo();
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

    startTheDisplay();

    // start WIFI
    wifi_init_sta();

    //connect to WIS web socket
    websocketSendBuffer = xMessageBufferCreate(websocketSendBufferLen);
    websocket_app_start(websocketSendBuffer, websocketSendBufferLen);
    
    //start websocket sending listening loop
    TaskHandle_t webSocketSendTask = NULL;                  //6*4096
    xTaskCreate(websocket_send_loop, "web_socket_send_task", 28*1024, NULL, 1, &webSocketSendTask);

    //start websocket pinger
    TaskHandle_t webSocketPingTask = NULL;
    xTaskCreate(ping_loop_task, "ping_loop_task", 4*1024, NULL, 1, &webSocketPingTask);

    //audio 
    setup_audio_buffer();
   
    //send audio task
    TaskHandle_t sendAudioTaskHandle = NULL;
    xTaskCreate(sendAudioChunk, "send_audio_chunk_task", 28*1024, websocketSendBuffer, 1, &sendAudioTaskHandle);

    //start microphone input AFTER STARTING AUDIO QUEUE
    TaskHandle_t microphoneTaskHandle = NULL;
    xTaskCreate(microphone_stream, "microphone_stream_task", 24*1024, NULL, 1, &microphoneTaskHandle);

#if MEM_MSG
    cout << "Free heap OGOGOG: ";
    cout << heap_caps_get_free_size(MALLOC_CAP_8BIT) << endl;
#endif

    return;
}