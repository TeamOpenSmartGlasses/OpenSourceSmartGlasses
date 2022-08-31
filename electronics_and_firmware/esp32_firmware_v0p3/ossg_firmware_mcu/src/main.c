/****************************************************************************
*
* This demo showcases BLE GATT server. It can send adv data, be connected by client.
* Run the gatt_client demo, the client demo will automatically connect to the gatt_server demo.
* Client demo will enable gatt_server's notify after connection. The two devices will then exchange
* data.
*
****************************************************************************/


#include "../lib/strings.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/message_buffer.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include <math.h>

#include "mbedtls/base64.h" //for encoding audio data to string

//web socket libs
#include "freertos/semphr.h"
#include "freertos/event_groups.h"
#include "esp_websocket_client.h"
#include "esp_event.h"

TickType_t lastTickTimeSend;
TickType_t lastTickTimeProc;

esp_websocket_client_handle_t webSocketClient;
static const char *audioJsonTemplate = "{\"MESSAGE_TYPE_LOCAL\" : \"AUDIO_CHUNK_DECRYPTED\", \"AUDIO_DATA\" : \"%s\"}";
// static const char *audioJsonTemplate = "%s";

//AUDIO**********************************************************************************************************************

// Save audio from PDM microphone to SD Card in wav format

/* Microphone has following pins:
    VDD
    GND
    DOUT - connected to DIN I2S pin on ESP32
    CLK  - connected to WS I2S pin on ESP32
    LR   - not connected to ESP32. Microphone has internal pull-down to GND for this pin. */

#include <driver/i2s.h>

// I2S perhiperhal number
#define I2S_CHANNEL                 I2S_NUM_0 // I2S_NUM_1 doesn't support PDM

// I2S pins
#define I2S_PIN_BIT_CLOCK           I2S_PIN_NO_CHANGE  // not used
#define I2S_PIN_WORD_SELECT         33 //OSSG_v0.3 built-in mic CLK
#define I2S_PIN_DATA_OUT            I2S_PIN_NO_CHANGE  // not used
#define I2S_PIN_DATA_IN             32 //OSSG_v0.3 built-in mic DATA_OUT

// I2S CONFIG PARAMS
#define SAMPLE_RATE 16000
const i2s_port_t I2S_PORT = I2S_NUM_0;
long total_read = 0;

/**************** Audio QUEUE HANDLER ***********************/
volatile uint8_t curr_audio_val = 0;
volatile bool audioSubscribed = false;
char WIS_IP[16];
const size_t AUDIO_BUFFER_SIZE = 1024;
const size_t DMA_BUF_SIZE = 256; //number of samples, not number of bytes
const size_t DMA_BUF_CNT = 2;

xQueueHandle audioQueue;
MessageBufferHandle_t audioMessageBuffer;
const size_t audioMessageBufferLen = (AUDIO_BUFFER_SIZE * sizeof(uint16_t)) + sizeof(size_t); // room for audio buffer, room for one size_t for MessageBuffer overhead

int packet_count = 0;

static const char *payload = "{\"MESSAGE_TYPE_LOCAL\" : \"AUDIO_CHUNK_DECRYPTED\", \"AUDIO_DATA\" : \"/+MYxAAEaAIEeUAQAgBgNgP/////KQQ/////Lvrg+lcWYHgtjadzsbTq+yREu495tq9c6v/7vt/of7mna9v6/btUnU17Jun9/+MYxCkT26KW+YGBAj9v6vUh+zab//v/96C3/pu6H+pv//r/ycIIP4pcWWTRBBBAMXgNdbRaABQAAABRWKwgjQVX0ECmrb///+MYxBQSM0sWWYI4A++Z/////////////0rOZ3MP//7H44QEgxgdvRVMXHZseL//540B4JAvMPEgaA4/0nHjxLhRgAoAYAgA/+MYxAYIAAJfGYEQAMAJAIAQMAwX936/q/tWtv/2f/+v//6v/+7qTEFNRTMuOTkuNVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV\"}";
//static const char *payload = "/+MYxAAEaAIEeUAQAgBgNgP/////KQQ/////Lvrg+lcWYHgtjadzsbTq+yREu495tq9c6v/7vt/of7mna9v6/btUnU17Jun9/+MYxCkT26KW+YGBAj9v6vUh+zab//v/96C3/pu6H+pv//r/ycIIP4pcWWTRBBBAMXgNdbRaABQAAABRWKwgjQVX0ECmrb///+MYxBQSM0sWWYI4A++Z/////////////0rOZ3MP//7H44QEgxgdvRVMXHZseL//540B4JAvMPEgaA4/0nHjxLhRgAoAYAgA/+MYxAYIAAJfGYEQAMAJAIAQMAwX936/q/tWtv/2f/+v//6v/+7qTEFNRTMuOTkuNVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV";

void addAudioChunkToQueue(uint8_t* buf)
{
    if (xQueueSend(audioQueue, buf, portMAX_DELAY) != pdPASS)
    {
        ESP_LOGE(PROGRAM_LOG_TAG, "TX AUDIO: Error sending the audio chunk to the audio queue.\n");
    }
}

// void receiveAudioChunkFromQueueTask()
// {
// 	int audioChunk = 0;
// 	while (1) {
// 		if (xQueueReceive(audioQueue, &audioChunk, portMAX_DELAY) != pdTRUE)
// 		{
// 			ESP_LOGE(PROGRAM_LOG_TAG, "RX AUDIO: Error receiving the audio chunk to the audio queue.\n");
// 		}
// 		else
// 		{
// 			ESP_LOGE(PROGRAM_LOG_TAG, "RX AUDIO: Successfully processed an audio chunk from the audio queue.\n");
// 		}
// 		vTaskDelay(pdMS_TO_TICKS(1500));
// 	}
// }

// const int DMA_BUFF_CT = 2;         //number of DMA buffer (minimum 2)
// const int DMA_BUFF_LEN = 32;       //samples per DMA buffer (minimum 8)

bool I2S_Init() {
//   i2s_config_t i2s_config;
//   memset(&i2s_config, 0, sizeof(i2s_config));

//   i2s_config.mode = (i2s_mode_t)I2S_MODE;
//   i2s_config.sample_rate =  I2S_SAMPLE_RATE;
//   i2s_config.bits_per_sample = I2S_BITS_PER_SAMPLE;
//   i2s_config.channel_format = I2S_CHANNEL_FMT;
//   i2s_config.communication_format = (i2s_comm_format_t)I2S_COMM_FMT;
//   i2s_config.intr_alloc_flags = I2S_INTERRUPT_PRIO;
//   i2s_config.dma_buf_count = I2S_DMA_BUF_COUNT;
//   i2s_config.dma_buf_len = I2S_DMA_BUF_SIZE;
//   i2s_config.use_apll = I2S_ENABLE_ACCURATE_CLK;

    // i2s_config.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM);     // Receive, not transfer
    // i2s_config.sample_rate = 16000;                    
    // i2s_config.bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT;                         //Number of bits per sample
    // i2s_config.channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT;                         //Do not connect SEL pin.
    // i2s_config.communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB);
    // i2s_config.intr_alloc_flags = ESP_INTR_FLAG_LEVEL1;                             // Interrupt level 1
    // i2s_config.dma_buf_count = DMA_BUFF_CT;                                         // number of buffers
    // i2s_config.dma_buf_len = DMA_BUFF_LEN;  


    // i2s_config_t i2s_config = {
    //      .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM),
    //      .sample_rate = SAMPLE_RATE,
    //      .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    //      .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    //     //  .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_LSB),
    //     // .communication_format = I2S_COMM_FORMAT_STAND_MSB,
    //     // .communication_format = I2S_COMM_FORMAT_I2S_MSB, //pcm data format
    //      .communication_format = I2S_COMM_FORMAT_STAND_PCM_SHORT,
    //      .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1, // high interrupt priority
    //      .dma_buf_count = DMA_BUF_CNT,
    //      .dma_buf_len = DMA_BUF_SIZE,  
    //     .use_apll = 0,
    //     };

    // i2s_config_t i2s_config = {
    //     .mode = I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM,
    //     .sample_rate = 16000,
    //     .bits_per_sample = 32,
    //     .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT, //OG used right left
    //     .communication_format = I2S_COMM_FORMAT_PCM,
    //     // .dma_buf_count = 2,
    //     // .dma_buf_len = 8,
    //      .dma_buf_count = DMA_BUF_CNT,
    //      .dma_buf_len = DMA_BUF_SIZE,  
    //     .use_apll = 0,
    //     .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1
    // };

    // pdm config for reading from left channel of PDM
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM),
        .sample_rate = 16000,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_PCM_SHORT,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 4,
        .dma_buf_len = 1024,
        .use_apll = false,
        .tx_desc_auto_clear = false,
        .fixed_mclk = 0
        };



  i2s_pin_config_t pins = {
    .bck_io_num = I2S_PIN_BIT_CLOCK,
    .ws_io_num =  I2S_PIN_WORD_SELECT,
    .data_out_num = I2S_PIN_DATA_OUT,
    .data_in_num = I2S_PIN_DATA_IN
  };

  if (i2s_driver_install(I2S_CHANNEL, &i2s_config, 0, NULL) != ESP_OK) {
    // Serial.println("i2s_driver_install() error");
    return false;
  }

//   i2s_set_pdm_rx_down_sample(I2S_CHANNEL, I2S_PDM_DSR_16S); //set to 16 so mic is in high performance mode

  if (i2s_set_pin(I2S_NUM_0, &pins) != ESP_OK) {
    // Serial.println("i2s_set_pin() error");
    return false;
  }

  return true;
}

void I2S_Quit() {
  if (i2s_driver_uninstall(I2S_CHANNEL) != ESP_OK) {
    // Serial.println("i2s_driver_uninstall() error");
  }
}

#define min(a,b) (((a)<(b))?(a):(b))

int i2s_read_custom(int16_t *samples, int count)
{
    int32_t raw_samples[256];
    int sample_index = 0;
    while (count > 0)
    {
        size_t bytes_read = 0;
        i2s_read(I2S_PORT, (void **)raw_samples, sizeof(int32_t) * min(count, 256), &bytes_read, portMAX_DELAY);
        int samples_read = bytes_read / sizeof(int32_t);
        for (int i = 0; i < samples_read; i++)
        {
            samples[sample_index] = (raw_samples[i] & 0xFFFFFFF0) >> 11;
            sample_index++;
            count--;
        }
    }
    return sample_index;
}

void microphone_stream() {
  // Initialize I2S
  I2S_Init();

  //count how many bytes we read from I2S
  uint32_t bytes_read;

  ESP_LOGI(PROGRAM_LOG_TAG, "Recording Started");

//   uint8_t* buf = (uint8_t*)malloc(AUDIO_BUFFER_SIZE);
  int16_t *buf = (int16_t *)malloc(sizeof(uint16_t) * AUDIO_BUFFER_SIZE);
  while (true) {
    // Read data from microphone
    // if (i2s_read(I2S_CHANNEL, buf, AUDIO_BUFFER_SIZE, &bytes_read, portMAX_DELAY) != ESP_OK) {
    //    ESP_LOGE(PROGRAM_LOG_TAG, "i2s_read() error");
    // }
    int samples_read = i2s_read_custom(buf, AUDIO_BUFFER_SIZE);
    int bytes_read = samples_read * sizeof(uint16_t);
    // printf("Bytes read: %d\n", bytes_read);

    // printf("Bytes read: %d\n", bytes_read);
    // printf("Proc period: %d\n", (xTaskGetTickCount() - lastTickTimeProc) * portTICK_PERIOD_MS);
    lastTickTimeProc = xTaskGetTickCount();
    
    if(samples_read != AUDIO_BUFFER_SIZE) {
       ESP_LOGE(PROGRAM_LOG_TAG, "Bytes written error");
    }

    //Print raw data
    // printf("Val1: %u \n", (uint16_t)((buf[0] << 8) | buf[1]));
    // printf("Val2: %u \n", (uint16_t)((buf[2] << 8) | buf[3]));
    // printf("Val3: %u \n", (uint16_t)((buf[4] << 8) | buf[5]));
    // printf("Val3+1: %u \n", (uint16_t)((buf[6] << 8) | buf[7]));
    // printf("Val1: %u \n", (uint16_t)(buf[0]));
    // printf("Val2: %u \n", (uint16_t)(buf[2]));
    // printf("Val3: %u \n", (uint16_t)(buf[4]));
    // printf("Val4: %u \n", (uint16_t)(buf[6]));
    //curr_audio_val = (uint8_t)buf[0];
    // printf("value of buf: %.*s\n", AUDIO_BUFFER_SIZE, buf);
    // printf("pointer of buf         : %p\n", buf);
    // addAudioChunkToQueue(buf);

    // send the bytes to the audio processor task
    size_t tx_bytes = xMessageBufferSend(audioMessageBuffer, buf, bytes_read, portMAX_DELAY);
    // printf("Number of transmitted bytes in message buffer: %d\n", tx_bytes);
    // printf("Sent to MB");
  }

    //free the buffer memory
    free(buf);

  ESP_LOGI(PROGRAM_LOG_TAG, "Recording finished");

  I2S_Quit();
}

//loop on receiving the latest audio chunk from the microphone and sending it to the WIS smart phone or cloud server
void sendAudioChunk(){
    audioSubscribed = true;
    while(true){
        uint8_t* audioChunk = (uint8_t*)malloc(audioMessageBufferLen);
        int bytes_written = xMessageBufferReceive(audioMessageBuffer, audioChunk, audioMessageBufferLen, portMAX_DELAY);
        lastTickTimeSend = xTaskGetTickCount();
        // printf("Received from MB this size buffer: %d\n", audioMessageBufferLen);
        // printf("Bytes written: %d\n", bytes_written);
        if (bytes_written != 0){
            if (audioSubscribed){
                // base 64 encode data and send it to the server
                int b64EncodedAudioBufferLen = ((ceil(bytes_written / 3.0 ) * 4) + 1); //size increase due to inefficieny of base64 //+1 for padding, or something
                // printf("Tryna b64: %d\n", b64EncodedAudioBufferLen);
                unsigned char * b64EncodedAudio = (unsigned char*)malloc(b64EncodedAudioBufferLen);
                size_t encodedAudioActualLen;
                int b64res = mbedtls_base64_encode(b64EncodedAudio, b64EncodedAudioBufferLen, &encodedAudioActualLen, (unsigned char *)audioChunk, (size_t)bytes_written);
                if(b64res == 0){
                    int jsonLength = b64EncodedAudioBufferLen + 256; //plus a bit for JSON extra info
                    char jsonAudioPacket[jsonLength];
                    snprintf(jsonAudioPacket, jsonLength, audioJsonTemplate, b64EncodedAudio);

                    //send JSON to WIS server
                    if (esp_websocket_client_is_connected(webSocketClient)) {
                        // printf("Sending audio to WIS...\n");
                        esp_websocket_client_send_text(webSocketClient, jsonAudioPacket, strlen(jsonAudioPacket), portMAX_DELAY);
                        // esp_websocket_client_send_text(webSocketClient, (char *)audioChunk, strlen((char *)audioChunk), portMAX_DELAY);
                    }
                } else{
                    ESP_LOGE(PROGRAM_LOG_TAG, "Base 64 encoding failed.");
                    free(b64EncodedAudio);
                    continue;
                }
                free(b64EncodedAudio);
            } else {
                vTaskDelay(pdMS_TO_TICKS(250));
            }
            // printf("Send time: %d\n", (xTaskGetTickCount() - lastTickTimeSend) * portTICK_PERIOD_MS);
        }
        free(audioChunk);
    }
}
// }

//WIFI***************************************************************************************************************************
/* The examples use WiFi configuration that you can set via project configuration menu
   If you'd rather not, just change the below entries to strings with
   the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
*/

#include "esp_wifi.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include <lwip/sockets.h>
#include <lwip/netdb.h>
#include <lwip/dns.h>

#define RECEIVER_IP_ADDR "255.255.255.255"
#define RECEIVER_PORT_NUM 8891
#define WIS_WEBSOCKET_COMMS_PORT 8887

#define EXAMPLE_ESP_MAXIMUM_RETRY  20

#if CONFIG_ESP_WIFI_AUTH_OPEN
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_OPEN
#elif CONFIG_ESP_WIFI_AUTH_WEP
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WEP
#elif CONFIG_ESP_WIFI_AUTH_WPA_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA2_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA_WPA2_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA_WPA2_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA3_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA3_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA2_WPA3_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_WPA3_PSK
#elif CONFIG_ESP_WIFI_AUTH_WAPI_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WAPI_PSK
#endif

/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t s_wifi_event_group;

/* The event group allows multiple bits for each event, but we only care about two events:
 * - we are connected to the AP with an IP
 * - we failed to connect after the maximum amount of retries */
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

static const char *TAG = DEVICE_NAME;

static int s_retry_num = 0;

int create_ipv4_socket()
{
  struct addrinfo hints;
  struct addrinfo *res;
  struct in_addr *addr;

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  
  int err = getaddrinfo(WIS_IP, "4567", &hints, &res);

  if(err != 0 || res == NULL) {
    printf("DNS lookup failed err=%d res=%p\n", err, res);
    return -1;
  }

  /* Code to print the resolved IP.

     Note: inet_ntoa is non-reentrant, look at ipaddr_ntoa_r for "real" code */
  addr = &((struct sockaddr_in *)res->ai_addr)->sin_addr;
  printf("DNS lookup succeeded. IP=%s\n", inet_ntoa(*addr));

  int l_sock = socket(res->ai_family, res->ai_socktype, 0);
  if(l_sock < 0) {
    printf("... Failed to allocate socket.\n");
    freeaddrinfo(res);
    return -1;
  }

  struct timeval to;
  to.tv_sec = 2;
  to.tv_usec = 0;
  setsockopt(l_sock,SOL_SOCKET,SO_SNDTIMEO,&to,sizeof(to));
  
  if(connect(l_sock, res->ai_addr, res->ai_addrlen) != 0) {
    printf("... socket connect failed errno=%d\n", errno);
    close(l_sock);
    freeaddrinfo(res);
    return -1;
  }

//   printf("... connected\n");
  freeaddrinfo(res);

  // All set, socket is configured for sending and receiving
  return l_sock;
}

void tcp_connect_task(){
    create_ipv4_socket();
    while(1){
        printf("HELLO WOLRD");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void udp_listen_task()
{

    printf("ASDF 1\n");
    while (1) {

        struct sockaddr_in dest_addr;
        dest_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        printf("ASDF 1.5\n");
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(RECEIVER_PORT_NUM);
        printf("ASDF 1.8\n");
        int addr_family = AF_INET;
        int ip_protocol = IPPROTO_IP;
        //inet_ntoa_r(dest_addr.sin_addr, RECEIVER_IP_ADDR, sizeof(RECEIVER_IP_ADDR) - 1);
        printf("ASDF 2\n");

//     ra.sin_family = AF_INET;
//     ra.sin_addr.s_addr = inet_addr(RECEIVER_IP_ADDR);
//     ra.sin_port = htons(RECEIVER_PORT_NUM);

        char data_buffer[80];

        int sock = socket(addr_family, SOCK_DGRAM, ip_protocol);
        if (sock < 0) {
            ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
            break;
        }
        printf("ASDF 3\n");
        //ESP_LOGI(TAG, "Socket created");

        int bc = 1;
        if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &bc, sizeof(bc)) < 0) {
            ESP_LOGE(TAG, "Failed to set sock options: errno %d", errno);
            closesocket(sock);
            break;
        }
        printf("ASDF 4\n");

        int err = bind(sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
        if (err < 0) {
            ESP_LOGE(TAG, "Socket unable to bind: err %d", err);
        }

        while (1) {

            printf("ASDF 5");
            struct sockaddr_in6 source_addr; 
            socklen_t socklen = sizeof(source_addr);
            printf("Listening on UDP...");
            int len = recvfrom(sock, &data_buffer, sizeof(data_buffer), 0, (struct sockaddr *)&source_addr, &socklen);
            printf("Received UDP data!");

            //Error occurred during receiving
            if (len < 0) {
                ESP_LOGE(TAG, "recvfrom failed: errno %d", errno);
                break;
            }
            // Data received
            else {

                // Get the sender's ip address as string
                if (source_addr.sin6_family == PF_INET) {
                    inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr.s_addr, RECEIVER_IP_ADDR, sizeof(RECEIVER_IP_ADDR) - 1);
                } else if (source_addr.sin6_family == PF_INET6) {
                    inet6_ntoa_r(source_addr.sin6_addr, RECEIVER_IP_ADDR, sizeof(RECEIVER_IP_ADDR) - 1);
                }
            }
        }

        if (sock != -1) {
            ESP_LOGE(TAG, "Shutting down socket and restarting...");
            shutdown(sock, 0);
            close(sock);
        }
    }
    vTaskDelete(NULL);
}

// void receive_thread(void *pvParameters)
// {
//     printf("Receive thread started... \n");

//     int socket_fd;
//     struct sockaddr_in sa,ra;

//     int recv_data; char data_buffer[80];
//     /* Creates an UDP socket (SOCK_DGRAM) with Internet Protocol Family (PF_INET).
//      * Protocol family and Address family related. For example PF_INET Protocol Family and AF_INET family are coupled.
//     */

//     socket_fd = socket(PF_INET, SOCK_DGRAM, 0);

//     if ( socket_fd < 0 )
//     {

//         printf("socket call failed");
//         exit(0);

//     }

//     memset(&sa, 0, sizeof(struct sockaddr_in));
//     ra.sin_family = AF_INET;
//     ra.sin_addr.s_addr = inet_addr(RECEIVER_IP_ADDR);
//     ra.sin_port = htons(RECEIVER_PORT_NUM);

//     int bc = 1;
//     if (setsockopt(socket_fd, SOL_SOCKET, SO_BROADCAST, &bc, sizeof(bc)) < 0) {
//         ESP_LOGE(TAG, "Failed to set sock options: errno %d", errno);
//         closesocket(socket_fd);
//         return;
//     }

//     /* Bind the UDP socket to the port RECEIVER_PORT_NUM and to the current
//     * machines IP address (Its defined by RECEIVER_PORT_NUM).
//     * Once bind is successful for UDP sockets application can operate
//     * on the socket descriptor for sending or receiving data.
//     */
//     if (bind(socket_fd, (struct sockaddr *)&ra, sizeof(struct sockaddr_in)) == -1)
//     {

//     printf("Bind to Port Number %d ,IP address %s failed\n",RECEIVER_PORT_NUM,RECEIVER_IP_ADDR);
//     close(socket_fd);
//     exit(1);
//     }
//     /* RECEIVER_PORT_NUM is port on which Server waits for data to
//     * come in. It copies the received data into receive buffer and
//     * prints the received data as string. If no data is available it
//     * blocks.recv calls typically return any availbale data on the socket instead of waiting for the entire data to come.
//     */

//     printf("Listening for data...\n");
//     recv_data = recv(socket_fd,data_buffer,sizeof(data_buffer),0);
//     printf("GOT DATA\n");
//     if(recv_data > 0)
//     {

//         data_buffer[recv_data] = '\0';
//         printf("%s\n",data_buffer);

//     }
//     close(socket_fd); 
// }

static void event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY) {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG, "retry to connect to the AP");
        } else {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
        }
        ESP_LOGI(TAG,"connect to the AP fail");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        snprintf(WIS_IP, sizeof(WIS_IP), IPSTR, IP2STR(&event->ip_info.ip));
        // snprintf(WIS_IP, sizeof(WIS_IP), "192.168.35.188"); //DEBUG, comment this line to connect to hotspot host
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
        //start listening for UDP packets - WIS server advertising itself
        //xTaskCreate(&udp_listen_task, "udp_listen_thread", 2048, NULL, 5, NULL);
        //xTaskCreate(&tcp_connect_task, "tcp_connect_thread", 2048, NULL, 5, NULL);
    }
}

void wifi_init_sta(void)
{
    ESP_LOGI(PROGRAM_LOG_TAG, "ESP_WIFI_MODE_STA");
    s_wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_netif_init());

    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_any_id));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_got_ip));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = EXAMPLE_ESP_WIFI_SSID,
            .password = EXAMPLE_ESP_WIFI_PASS,
            /* Setting a password implies station will connect to all security modes including WEP/WPA.
             * However these modes are deprecated and not advisable to be used. Incase your Access point
             * doesn't support WPA2, these mode can be enabled by commenting below line */
	     .threshold.authmode = WIFI_AUTH_OPEN, //change this to change minimum acceptable security level
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config) );
    ESP_ERROR_CHECK(esp_wifi_start() );

    ESP_LOGI(TAG, "wifi_init_sta finished.");

    /* Waiting until either the connection is established (WIFI_CONNECTED_BIT) or connection failed for the maximum
     * number of re-tries (WIFI_FAIL_BIT). The bits are set by event_handler() (see above) */
    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
            WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
            pdFALSE,
            pdFALSE,
            portMAX_DELAY);

    /* xEventGroupWaitBits() returns the bits before the call returned, hence we can test which event actually
     * happened. */
    if (bits & WIFI_CONNECTED_BIT) {
        ESP_LOGI(TAG, "connected to ap SSID:%s password:%s",
                 EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
    } else if (bits & WIFI_FAIL_BIT) {
        ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s",
                 EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
    } else {
        ESP_LOGE(TAG, "UNEXPECTED EVENT");
    }
}

//WEB SOCKET ********************************************************************************************


#define NO_DATA_TIMEOUT_SEC 10

static TimerHandle_t shutdown_signal_timer;
static SemaphoreHandle_t shutdown_sema;

static void shutdown_signaler(TimerHandle_t xTimer)
{
    ESP_LOGI(TAG, "No data received for %d seconds, signaling shutdown", NO_DATA_TIMEOUT_SEC);
    xSemaphoreGive(shutdown_sema);
}

static void websocket_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    esp_websocket_event_data_t *data = (esp_websocket_event_data_t *)event_data;
    switch (event_id) {
    case WEBSOCKET_EVENT_CONNECTED:
        ESP_LOGI(TAG, "WEBSOCKET_EVENT_CONNECTED");
        break;
    case WEBSOCKET_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "WEBSOCKET_EVENT_DISCONNECTED");
        break;
    case WEBSOCKET_EVENT_DATA:
        ESP_LOGI(TAG, "WEBSOCKET_EVENT_DATA");
        ESP_LOGI(TAG, "Received opcode=%d", data->op_code);
        ESP_LOGW(TAG, "Received=%.*s", data->data_len, (char *)data->data_ptr);
        ESP_LOGW(TAG, "Total payload length=%d, data_len=%d, current payload offset=%d\r\n", data->payload_len, data->data_len, data->payload_offset);

        //xTimerReset(shutdown_signal_timer, portMAX_DELAY);
        break;
    case WEBSOCKET_EVENT_ERROR:
        ESP_LOGI(TAG, "WEBSOCKET_EVENT_ERROR");
        break;
    }
}

static void websocket_app_start()
{
    esp_websocket_client_config_t websocket_cfg = {};

    // shutdown_signal_timer = xTimerCreate("Websocket shutdown timer", NO_DATA_TIMEOUT_SEC * 1000 / portTICK_PERIOD_MS,
    //                                      pdFALSE, NULL, shutdown_signaler);
    shutdown_sema = xSemaphoreCreateBinary();

    //websocket url/IP and port
    // websocket_cfg.uri = WIS_IP;
    int wsUriLen = 1024;
    char wsUri[wsUriLen];
    snprintf(wsUri, wsUriLen, "ws://%s", WIS_IP);
    // printf("WEBSOCKET address: %s", wsUri);
    // websocket_cfg.uri = wsUri;
    // websocket_cfg.uri = "ws://192.168.35.188";
    // websocket_cfg.uri = "ws://192.168.18.157";
    websocket_cfg.uri = "ws://192.168.35.187";
    websocket_cfg.port = 8887;

    ESP_LOGI(TAG, "Connecting to %s...", websocket_cfg.uri);

    webSocketClient = esp_websocket_client_init(&websocket_cfg);
    esp_websocket_register_events(webSocketClient, WEBSOCKET_EVENT_ANY, websocket_event_handler, (void *)webSocketClient);

    esp_websocket_client_start(webSocketClient);
    audioSubscribed = true;
    // xTimerStart(shutdown_signal_timer, portMAX_DELAY);
    char data[32];
    int i = 0;
    while (true) {
        // if (esp_websocket_client_is_connected(webSocketClient)) {
        //     int len = sprintf(data, "hello %04d", i++);
        //     ESP_LOGI(TAG, "Sending %s of size %d", payload, strlen(payload));
        //     esp_websocket_client_send_text(webSocketClient, payload, strlen(payload), portMAX_DELAY);
        // }
        vTaskDelay(1000 / portTICK_RATE_MS);
    }

    xSemaphoreTake(shutdown_sema, portMAX_DELAY);
    audioSubscribed = false;
    esp_websocket_client_stop(webSocketClient);
    ESP_LOGI(TAG, "Websocket Stopped");
    esp_websocket_client_destroy(webSocketClient);
}


//AUDIO WIFI SENDING COMMS TCP SOCKET

#include <string.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "lwip/err.h"
#include "lwip/sockets.h"


//TCP connection params
#define HOST_IP_ADDR "192.168.66.144"
#define PORT 4567


// static void tcp_client_task(void *pvParameters)
// {
//     char rx_buffer[128];
//     char host_ip[] = HOST_IP_ADDR;
//     int addr_family = 0;
//     int ip_protocol = 0;

//     struct sockaddr_in dest_addr;
//     dest_addr.sin_addr.s_addr = inet_addr(host_ip);
//     dest_addr.sin_family = AF_INET;
//     dest_addr.sin_port = htons(PORT);
//     addr_family = AF_INET;
//     ip_protocol = IPPROTO_IP;
//     int sock =  socket(addr_family, SOCK_STREAM, ip_protocol);
//     if (sock < 0) {
//         ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
//         return;
//     }
//     ESP_LOGI(TAG, "Socket created, connecting to %s:%d", host_ip, PORT);

//     int err = connect(sock, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr_in6));
//     if (err != 0) {
//         ESP_LOGE(TAG, "Socket unable to connect: errno %d", errno);
//         return;
//     }
//     ESP_LOGI(TAG, "Successfully connected");

//     while (1) {
//         // ESP_LOGI(TAG, "Sending message over audio socket");
//         // int err = send(sock, payload, strlen(payload), 0);
//         // if (err < 0) {
//         //     ESP_LOGE(TAG, "Error occurred during sending: errno %d", errno);
//         //     break;
//         // }

//         // int len = recv(sock, rx_buffer, sizeof(rx_buffer) - 1, 0);
//         // // Error occurred during receiving
//         // if (len < 0) {
//         //     ESP_LOGE(TAG, "recv failed: errno %d", errno);
//         //     break;
//         // }
//         // // Data received
//         // else {
//         //     rx_buffer[len] = 0; // Null-terminate whatever we received and treat like a string
//         //     ESP_LOGI(TAG, "Received %d bytes from %s:", len, host_ip);
//         //     ESP_LOGI(TAG, "%s", rx_buffer);
//         // }

//         vTaskDelay(100 / portTICK_PERIOD_MS);
//     }

    // if (sock != -1) {
    //     ESP_LOGE(TAG, "Shutting down socket and restarting...");
    //     shutdown(sock, 0);
    //     close(sock);
    // }

//     while(1){
//         vTaskDelay(3000 / portTICK_PERIOD_MS);
//     }

//     vTaskDelete(NULL);
// }


void app_main(void)
{
    esp_err_t ret;

    // Initialize NVS.
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    //create event loop
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    //start WIFI
    wifi_init_sta();

    //connect to WIS web socket
    esp_log_level_set("WEBSOCKET_CLIENT", ESP_LOG_DEBUG);
    TaskHandle_t webSocketTask = NULL;
    xTaskCreate(websocket_app_start, "web_socket_task", 6*4096, NULL, 1, &webSocketTask);

    //connect to audio TCP socket stream
    // esp_log_level_set("TRANS_TCP", ESP_LOG_DEBUG);
    //xTaskCreate(tcp_client_task, "tcp_client", 4096, NULL, 5, NULL);

     /************************* Create audio buffer****************************/
    audioMessageBuffer = xMessageBufferCreate(audioMessageBufferLen * 4); //hold n message at once, where n is the constant multiplier
    assert(audioMessageBuffer);
    audioQueue = xQueueCreate(250, sizeof(uint8_t*));
    if (audioQueue == 0)  // Queue not created
    {
        ESP_LOGE(PROGRAM_LOG_TAG, "Unable to create audio queue.\n");
    } else {
        ESP_LOGE(PROGRAM_LOG_TAG, "Audio queue created successfully.\n");
    }

    //send audio task
    TaskHandle_t sendAudioTaskHandle = NULL;
    xTaskCreate(sendAudioChunk, "send_audio_chunk_task", 6*4096, NULL, 1, &sendAudioTaskHandle);

    //start microphone input AFTER STARTING AUDIO QUEUE
    TaskHandle_t microphoneTaskHandle = NULL;
    xTaskCreate(microphone_stream, "microphone_stream_task", 6*4096, NULL, 1, &microphoneTaskHandle);

    return;
}