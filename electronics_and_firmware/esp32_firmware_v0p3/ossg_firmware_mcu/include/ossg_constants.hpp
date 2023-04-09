#include <string>
#include <stack>
using std::string;
#define PROGRAM_LOG_TAG "OSSG_esp32"
#define DEVICE_NAME "SmartGlasses_OSSG"

//WIFI
//#define EXAMPLE_ESP_WIFI_SSID      "WearNet2"
//#define EXAMPLE_ESP_WIFI_PASS      "ciqi8591"
#define ALEX true
#if ALEX
    static char* esp_wifi_ssid = "WearNetAlex";
    static char* esp_wifi_pass = "ciqi8591";
#else
    static char* esp_wifi_ssid = "WearNet2";
    static char* esp_wifi_pass = "7777777crc";
#endif