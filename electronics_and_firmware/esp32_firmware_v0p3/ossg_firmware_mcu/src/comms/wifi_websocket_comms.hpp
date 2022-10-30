#include "freertos/FreeRTOS.h"
#include "freertos/message_buffer.h"

extern bool check_websocket_connect();
extern int create_ipv4_socket();
extern void tcp_connect_task();
extern void udp_listen_task();
extern void update_ws_ip();
extern void wifi_init_sta();
extern void websocket_send_loop(void *args);
extern void ping_loop_task(void *args);
extern void websocket_send_text(char * text);
extern void websocket_app_start(MessageBufferHandle_t websocketSendBuffer, size_t websocketSendBufferLen, MessageBufferHandle_t eventsBuffer);