# Setup

1. Install VSCODE
2. Install platformio in VSCODE
3. a) If your ESP32 has PSRAM, enable PSRAM in menuconfig. Otherwise, disable PSRAM in menuconfig
```
platformio run -t menuconfig
```
Component config -> ESP32 Specific -> SPIRAM/PSRAM Enable/Disable  
b) Comment/uncomment PSRAM lines from platformio.ini depending on your ESP32 hardware
