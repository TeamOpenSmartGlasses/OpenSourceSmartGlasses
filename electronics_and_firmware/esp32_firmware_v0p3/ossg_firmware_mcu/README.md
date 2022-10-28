# Setup

1. Install VSCODE
2. Install platformio in VSCODE
3. a) If your ESP32 has PSRAM, enable PSRAM in menuconfig. Otherwise, disable PSRAM in menuconfig
```
platformio run -t menuconfig
```
Component config -> ESP32 Specific -> SPIRAM/PSRAM Enable/Disable  
b) Comment/uncomment PSRAM lines from platformio.ini depending on your ESP32 hardware

# Gotchas

If build goes well and then at the very end you get undefined reference to a task function that doesn't take arguments, make sure you have it take the `void *args` argument.

# TODO

* Search engine result
* Command success page (success? And what the command did)
* Screen to stream in new text (live life captions/speech translate)