// WIFI***************************************************************************************************************************
/* The examples use WiFi configuration that you can set via project configuration menu
   If you'd rather not, just change the below entries to strings with
   the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
*/

#include "../include/ossg_constants.hpp"

#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "freertos/message_buffer.h"

//wifi import
#include "esp_wifi.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include <lwip/sockets.h>
#include <lwip/netdb.h>
#include <lwip/dns.h>

// web socket libs
#include "freertos/semphr.h"
#include "freertos/event_groups.h"
#include "esp_websocket_client.h"
#include "esp_event.h"

//actual web socket object
esp_websocket_client_handle_t webSocketClient;

//message buffer to handle receiving payloads to send over buffer
MessageBufferHandle_t localWebsocketSendBuffer;
size_t localWebsocketSendBufferLen;
MessageBufferHandle_t localEventsBuffer;

//wifi vars/constants
char WIS_IP[16];
char WIS_WEBSOCKET_IP[16];

#define RECEIVER_IP_ADDR "255.255.255.255"
#define RECEIVER_PORT_NUM 8891
#define WIS_WEBSOCKET_COMMS_PORT 8887

#define EXAMPLE_ESP_MAXIMUM_RETRY 100000

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
#define WIFI_FAIL_BIT BIT1

static const char *TAG = "WIFI_WEBSOCKET_COMMS_OSSG";

static int s_retry_num = 0;

int create_ipv4_socket()
{
    struct addrinfo hints;
    struct addrinfo *res;
    struct in_addr *addr;

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int err = getaddrinfo(WIS_IP, "4567", &hints, &res);

    if (err != 0 || res == NULL)
    {
        printf("DNS lookup failed err=%d res=%p\n", err, res);
        return -1;
    }

    /* Code to print the resolved IP.

       Note: inet_ntoa is non-reentrant, look at ipaddr_ntoa_r for "real" code */
    addr = &((struct sockaddr_in *)res->ai_addr)->sin_addr;
    printf("DNS lookup succeeded. IP=%s\n", inet_ntoa(*addr));

    int l_sock = socket(res->ai_family, res->ai_socktype, 0);
    if (l_sock < 0)
    {
        printf("... Failed to allocate socket.\n");
        freeaddrinfo(res);
        return -1;
    }

    struct timeval to;
    to.tv_sec = 2;
    to.tv_usec = 0;
    setsockopt(l_sock, SOL_SOCKET, SO_SNDTIMEO, &to, sizeof(to));

    if (connect(l_sock, res->ai_addr, res->ai_addrlen) != 0)
    {
        printf("... socket connect failed errno=%d\n", errno);
        close(l_sock);
        freeaddrinfo(res);
        return -1;
    }

    freeaddrinfo(res);

    // All set, socket is configured for sending and receiving
    return l_sock;
}

void tcp_connect_task()
{
    create_ipv4_socket();
    while (1)
    {
        printf("HELLO WOLRD");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void udp_listen_task()
{

    printf("ASDF 1\n");
    while (1)
    {
        struct sockaddr_in dest_addr;
        dest_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        printf("ASDF 1.5\n");
        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(RECEIVER_PORT_NUM);
        printf("ASDF 1.8\n");
        int addr_family = AF_INET;
        int ip_protocol = IPPROTO_IP;
        // inet_ntoa_r(dest_addr.sin_addr, RECEIVER_IP_ADDR, sizeof(RECEIVER_IP_ADDR) - 1);
        printf("ASDF 2\n");

        //     ra.sin_family = AF_INET;
        //     ra.sin_addr.s_addr = inet_addr(RECEIVER_IP_ADDR);
        //     ra.sin_port = htons(RECEIVER_PORT_NUM);

        char data_buffer[80];

        int sock = socket(addr_family, SOCK_DGRAM, ip_protocol);
        if (sock < 0)
        {
            ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
            break;
        }
        printf("ASDF 3\n");
        // ESP_LOGI(TAG, "Socket created");

        int bc = 1;
        if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &bc, sizeof(bc)) < 0)
        {
            ESP_LOGE(TAG, "Failed to set sock options: errno %d", errno);
            closesocket(sock);
            break;
        }
        printf("ASDF 4\n");

        int err = bind(sock, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
        if (err < 0)
        {
            ESP_LOGE(TAG, "Socket unable to bind: err %d", err);
        }

        while (1)
        {

            printf("ASDF 5");
            struct sockaddr_in6 source_addr;
            socklen_t socklen = sizeof(source_addr);
            printf("Listening on UDP...");
            int len = recvfrom(sock, &data_buffer, sizeof(data_buffer), 0, (struct sockaddr *)&source_addr, &socklen);
            printf("Received UDP data!");

            // Error occurred during receiving
            if (len < 0)
            {
                ESP_LOGE(TAG, "recvfrom failed: errno %d", errno);
                break;
            }
            // Data received
            else
            {

                // Get the sender's ip address as string
                if (source_addr.sin6_family == PF_INET)
                {
                    inet_ntoa_r(((struct sockaddr_in *)&source_addr)->sin_addr.s_addr, RECEIVER_IP_ADDR, sizeof(RECEIVER_IP_ADDR) - 1);
                }
                else if (source_addr.sin6_family == PF_INET6)
                {
                    inet6_ntoa_r(source_addr.sin6_addr, RECEIVER_IP_ADDR, sizeof(RECEIVER_IP_ADDR) - 1);
                }
            }
        }

        if (sock != -1)
        {
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

bool check_websocket_connect(){
    return esp_websocket_client_is_connected(webSocketClient);
}

// this should be done within websocket, but it works for now
void update_ws_ip()
{
    if (!esp_websocket_client_is_connected(webSocketClient))
    {
        int wsUriLen = 1024;
        char wsUri[wsUriLen];
        snprintf(wsUri, wsUriLen, "ws://%s", WIS_WEBSOCKET_IP);
        esp_websocket_client_set_uri(webSocketClient, wsUri);
    }
}

static void event_handler(void *arg, esp_event_base_t event_base,
                          int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        esp_wifi_connect();
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        // kill websocket
        if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY)
        {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG, "retry to connect to the AP");
        }
        else
        {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
        }
        ESP_LOGI(TAG, "connect to the AP fail");
    }
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
        ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
        snprintf(WIS_IP, sizeof(WIS_IP), IPSTR, IP2STR(&event->ip_info.ip));
        snprintf(WIS_WEBSOCKET_IP, sizeof(WIS_WEBSOCKET_IP), IPSTR, IP2STR(&event->ip_info.gw));
        printf("WIS_IP is %s", WIS_IP);
        printf("WIS_WEBSOCKET_IP is %s", WIS_WEBSOCKET_IP);
        update_ws_ip();
        // snprintf(WIS_IP, sizeof(WIS_IP), "192.168.15.188"); //DEBUG for testing, uncomment this line to connect to hotspot host
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
        // start listening for UDP packets - WIS server advertising itself
        // xTaskCreate(&udp_listen_task, "udp_listen_thread", 2048, NULL, 5, NULL);
        // xTaskCreate(&tcp_connect_task, "tcp_connect_thread", 2048, NULL, 5, NULL);
    }
}

void wifi_init_sta()
{
    ESP_LOGI(PROGRAM_LOG_TAG, "ESP_WIFI_MODE_STA");
    s_wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_netif_init());

    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

#if MEM_MSG
    cout << "Free heap RIGHT BEFORE WIFI INIT: ";
    cout << heap_caps_get_free_size(MALLOC_CAP_8BIT) << endl;
#endif
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    //esp_wifi_init(&cfg);
#if MEM_MSG
    cout << "Free heap RIGHT AFTER WIFI INIT: ";
    cout << heap_caps_get_free_size(MALLOC_CAP_8BIT) << endl;
#endif
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
    /*
        wifi_config_t wifi_config = {
            .sta = {
                .ssid = EXAMPLE_ESP_WIFI_SSID,
                .password = EXAMPLE_ESP_WIFI_PASS,
                .threshold.authmode = WIFI_AUTH_OPEN, //change this to change minimum acceptable security level

                // Setting a password implies station will connect to all security modes including WEP/WPA.
                // However these modes are deprecated and not advisable to be used. Incase your Access point
                // doesn't support WPA2, these mode can be enabled by commenting below line
            },
        };
    */
    // C++ version of the above
    wifi_config_t wifi_config = {};
    strcpy((char *)wifi_config.sta.ssid, esp_wifi_ssid);
    strcpy((char *)wifi_config.sta.password, esp_wifi_pass);
    wifi_config.sta.threshold.authmode = WIFI_AUTH_OPEN;

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

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
    if (bits & WIFI_CONNECTED_BIT)
    {
        ESP_LOGI(TAG, "connected to ap SSID:%s password:%s",
                 esp_wifi_ssid, esp_wifi_pass);
    }
    else if (bits & WIFI_FAIL_BIT)
    {
        ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s",
                 esp_wifi_ssid, esp_wifi_pass);
    }
    else
    {
        ESP_LOGE(TAG, "UNEXPECTED EVENT");
    }
}

// WEB SOCKET ********************************************************************************************

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
    switch (event_id)
    {
    case WEBSOCKET_EVENT_CONNECTED:
        ESP_LOGI(TAG, "WEBSOCKET_EVENT_CONNECTED");
        break;
    case WEBSOCKET_EVENT_DISCONNECTED:
    case WEBSOCKET_EVENT_CLOSED:
        ESP_LOGI(TAG, "WEBSOCKET_EVENT_DISCONNECTED or CLOSED");
        ESP_LOGE(TAG, "Websocket disconnected, sleeping briefly then restarting...");
        vTaskDelay(pdMS_TO_TICKS(1000));
        esp_restart();
        // reconnect
        break;
    case WEBSOCKET_EVENT_DATA:
        {
        // ESP_LOGI(TAG, "WEBSOCKET_EVENT_DATA");
        //  ESP_LOGI(TAG, "Received opcode=%d", data->op_code);
        //  ESP_LOGW(TAG, "Received=%.*s", data->data_len, (char *)data->data_ptr);
        //  ESP_LOGW(TAG, "Total payload length=%d, data_len=%d, current payload offset=%d\r\n", data->payload_len, data->data_len, data->payload_offset);
         if (data->data_len > 5){ //ignore empty strings and tiny pings
            int jsonStringLen = (data->data_len)+1;
            char *jsonString = (char*)malloc(jsonStringLen);
            snprintf(jsonString, jsonStringLen, "%s", (char *)data->data_ptr);
            //  ESP_LOGW(TAG, "JSON STRING PREPARSE=%s", jsonString);
            size_t tx_bytes = xMessageBufferSend(localEventsBuffer, jsonString, strlen(jsonString)+1, portMAX_DELAY);
            free(jsonString);
         }
        break;
        }
    case WEBSOCKET_EVENT_ERROR:
        printf("WEBSOCKET_EVENT_ERROR");
        break;
    default:
        ESP_LOGI(TAG, "WEBSOCKET EVENT WAS: %d", event_id);
    }
}

static void reconnect_websocket()
{
    // close down the socket
    esp_websocket_client_close(webSocketClient, portMAX_DELAY);

    // connect the socket again
}

#include "message_types.hpp"
void ping_loop_task(void *args)
{
    while (true)
    {
        if (check_websocket_connect())
        {
            //MessageTypes mt = MessageTypes();
            char ping[64] = "{\"MESSAGE_TYPE_LOCAL\" : \"ping\"}";
            esp_websocket_client_send_text(webSocketClient, ping, strlen(ping), portMAX_DELAY);
        }
        vTaskDelay(1500 / portTICK_RATE_MS);
    }
}

void websocket_app_start(MessageBufferHandle_t websocketSendBuffer, size_t websocketSendBufferLen, MessageBufferHandle_t eventsBuffer)
{
    localWebsocketSendBuffer = websocketSendBuffer;
    localWebsocketSendBufferLen = websocketSendBufferLen;
    localEventsBuffer = eventsBuffer;

    esp_websocket_client_config_t websocket_cfg = {};

    // shutdown_signal_timer = xTimerCreate("Websocket shutdown timer", NO_DATA_TIMEOUT_SEC * 1000 / portTICK_PERIOD_MS,
    //                                      pdFALSE, NULL, shutdown_signaler);
    shutdown_sema = xSemaphoreCreateBinary();

    // websocket url/IP and port
    int wsUriLen = 1024;
    char wsUri[wsUriLen];
    snprintf(wsUri, wsUriLen, "ws://%s", WIS_WEBSOCKET_IP);
    websocket_cfg.uri = wsUri;
    websocket_cfg.port = 8887;

    ESP_LOGI(TAG, "Connecting to %s...", websocket_cfg.uri);

    webSocketClient = esp_websocket_client_init(&websocket_cfg);
    esp_websocket_register_events(webSocketClient, WEBSOCKET_EVENT_ANY, websocket_event_handler, (void *)webSocketClient);

    esp_websocket_client_start(webSocketClient);
}

void websocket_send_loop(void *args){
    char * stringToSend = (char *)malloc(localWebsocketSendBufferLen);
    while (true)
    {
        int bytes_written = xMessageBufferReceive(localWebsocketSendBuffer, stringToSend, localWebsocketSendBufferLen, portMAX_DELAY);

        if (bytes_written != 0){
            if (check_websocket_connect()) {
                //ESP_LOGI(TAG, "Sending message of size %d", strlen(stringToSend));
                esp_websocket_client_send_text(webSocketClient, stringToSend, strlen(stringToSend), portMAX_DELAY);
            }
        }
    }
    free(stringToSend);
}

// AUDIO WIFI SENDING COMMS TCP SOCKET

// #include <string.h>
// #include <sys/param.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "freertos/event_groups.h"
// #include "esp_system.h"
// #include "esp_wifi.h"
// #include "esp_event.h"
// #include "esp_log.h"
// #include "nvs_flash.h"
// #include "esp_netif.h"
// #include "lwip/err.h"
// #include "lwip/sockets.h"

// #ifdef WEBSOCKET_RECONNECT_TIMEOUT_MS
// #undef WEBSOCKET_RECONNECT_TIMEOUT_MS
// #define WEBSOCKET_RECONNECT_TIMEOUT_MS (500) // change timeout of websocket retry in milliseconds
// #endif

// // TCP connection params
// #define HOST_IP_ADDR "192.168.66.144"
// #define PORT 4567

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
// }

void websocket_send_text(char * text){
    esp_websocket_client_send_text(webSocketClient, text, strlen(text)+1, portMAX_DELAY);
}