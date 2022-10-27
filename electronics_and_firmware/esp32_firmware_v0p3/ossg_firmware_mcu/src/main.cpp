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

 // ESP32 PSRAM bug workaround (use when the library is NOT compiled with PSRAM hack enabled)
  // Place between a write and a read PSRAM operation (write->ASM_MEMW->read), not viceversa
  #define ASM_MEMW asm(" MEMW");

  #define ASM_NOP asm(" NOP");

  #define PSRAM_WORKAROUND1 asm(" nop;nop;nop;nop");
  #define PSRAM_WORKAROUND2 asm(" memw");

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

    // start WIFI
    wifi_init_sta();

    //connect to WIS web socket
    websocketSendBuffer = xMessageBufferCreate(websocketSendBufferLen);
    websocket_app_start(websocketSendBuffer, websocketSendBufferLen);
    
    //start websocket receive listening loop
    esp_log_level_set("WEBSOCKET_CLIENT", ESP_LOG_DEBUG);
    TaskHandle_t webSocketReceiveTask = NULL;                  //6*4096
    //xTaskCreatePinnedToCore(websocket_receive_loop, "web_socket_receive_task", 4*1024, NULL, 1, &webSocketReceiveTask, 0);

    //start websocket sending listening loop
    TaskHandle_t webSocketSendTask = NULL;                  //6*4096
    xTaskCreatePinnedToCore(websocket_send_loop, "web_socket_send_task", 12*1024, NULL, 1, &webSocketSendTask, 0);

    //start websocket pinger
    TaskHandle_t webSocketPingTask = NULL;
    xTaskCreatePinnedToCore(ping_loop_task, "ping_loop_task", 4*1024, NULL, 1, &webSocketPingTask, 0);

    //connect to audio TCP socket stream
    // esp_log_level_set("TRANS_TCP", ESP_LOG_DEBUG);
    //xTaskCreate(tcp_client_task, "tcp_client", 4096, NULL, 5, NULL);

    //audio 
    setup_audio_buffer();
   
    //send audio task
    TaskHandle_t sendAudioTaskHandle = NULL;
    xTaskCreate(sendAudioChunk, "send_audio_chunk_task", 6*4096, websocketSendBuffer, 1, &sendAudioTaskHandle);

    //start microphone input AFTER STARTING AUDIO QUEUE
    TaskHandle_t microphoneTaskHandle = NULL;
    xTaskCreate(microphone_stream, "microphone_stream_task", 6*4096, NULL, 1, &microphoneTaskHandle);
    startTheDisplay();

#if MEM_MSG
    cout << "Free heap OGOGOG: ";
    cout << heap_caps_get_free_size(MALLOC_CAP_8BIT) << endl;
#endif

    return;
}