# OSSG Firmware

## Features

* Displays pretty UI over composite video using LovyanGFX + LVGL
* Streams recoreded audio to an Android device
* Receives JSON commands from an Android device
## Setup

1. Install VSCODE
2. Install platformio in VSCODE
3. a) If your ESP32 has PSRAM, enable PSRAM in menuconfig. Otherwise, disable PSRAM in menuconfig
```
platformio run -t menuconfig
```
Component config -> ESP32 Specific -> SPIRAM/PSRAM Enable/Disable  
b) Comment/uncomment PSRAM lines from platformio.ini depending on your ESP32 hardware

## Gotchas

If build goes well and then at the very end you get undefined reference to a task function that doesn't take arguments, make sure you have it take the `void *args` argument.

## TODO

* Search engine result
* Command success page (success? And what the command did)
* Screen to stream in new text (live life captions/speech translate)

## History

This project is heavily inspired by the combination of two projects that came before it:

* The [Wearable Intelligence System](https://github.com/emexlabs/WearableIntelligenceSystem), a platform to be used with Android-based smartglasses such as the Vuzix Blade, designed for extending our mental capabilities. By Cayden Pierce.

* The [Telescope](https://github.com/alex1115alex/Wearables-Telescope), a Google Glass-inspired project designed to be as compact and cheap as possible by taking advantage of the ESP32's composite video output capabilities. By Alex Israelov.