# Open Source Smart Glasses Firmware

This firmware serves as a thin client for the [Wearable Intelligence System](https://github.com/emexlabs/WearableIntelligenceSystem) (WIS), powered by the ESP32. The WIS Android smart phone (ASP) and GNU/Linux Box (GLBOX) servers handle all of the processing, logic, AI, etc., and this firmware sends signals to the WIS and receives UI prompts from the WIS (i.e. a thin client). See the [WIS](https://github.com/emexlabs/WearableIntelligenceSystem) for the ASP + GLBOX, as well as another frontend with the same API but designed for Android-powered smart glasses (ASG).

## Key features

* Outputs GUI to a display over composite video using LovyanGFX + LVGL
* Streams audio to the WIS
* Receives commands from the WIS
* Supported modes:
    * Contextual search engine
    * Live language translation
    * Live captioning

## Setup

1. Install [VSCode](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide) and set up environment for ESP32 & ESPIDF.
3. Download git submodules (`git submodule update --init`) if you haven't already
4. Open the `electronics_and_firmware/esp32_firmware_v0p3/ossg_firmware_mcu/` folder in VSCode.
5. Use PlatformIO's `Build and Upload` button.

## Gotchas

If build goes well and then at the very end you get undefined reference to a task function that doesn't take arguments, make sure you have it take the `void *args` argument.

## TODO

* Search engine result
* Command success page (success? And what the command did)
* Make text streaming more efficient. It gets laggy with large amounts of text.

## History

This project's display solution is heavily inspired by the [Telescope](https://github.com/alex1115alex/Wearables-Telescope), a Google Glass-inspired project designed to be as compact and cheap as possible by taking advantage of the ESP32's composite video output capabilities. By Alex Israelov.