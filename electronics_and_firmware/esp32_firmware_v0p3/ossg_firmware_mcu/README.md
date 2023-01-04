# OSSG Firmware

This firmware serves as as smart glasses thin client for the [Wearable Intelligence System](https://github.com/emexlabs/WearableIntelligenceSystem) (WIS) for smart glasses powered by ESP32. The WIS Android smart phone (ASP) and GNU/Linux Box (GLBOX) servers handle all of the processing, logic, AI, etc., and this firmware sends signals to the WIS and receives UI prompts from the WIS (i.e. a thin client). See the [WIS](https://github.com/emexlabs/WearableIntelligenceSystem) for the ASP + GLBOX, as well as another frontend with the same API but designed for Android-powered smart glasses (ASG).

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

This project's display solution is heavily inspired by the [Telescope](https://github.com/alex1115alex/Wearables-Telescope), a Google Glass-inspired project designed to be as compact and cheap as possible by taking advantage of the ESP32's composite video output capabilities. By Alex Israelov.