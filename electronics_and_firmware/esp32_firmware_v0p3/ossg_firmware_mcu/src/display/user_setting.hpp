//#include <stdio.h>
//#include <freertos/FreeRTOS.h>
//#include <freertos/task.h>
//#include "sdkconfig.h"


//#include "../lib/LovyanGFX/src/lgfx/v1/platforms/esp32/Panel_CVBS.hpp"
//#include "../lib/LovyanGFX/src/lgfx/v1/platforms/esp32s2/Bus_Parallel16.hpp"


#define LGFX_USE_V1
#define LGFX_CVBS
#define LGFX_ESP_WROVER_KIT

#include <iostream>
#include <LovyanGFX.hpp>
#include <driver/i2c.h>
#include "global_settings.hpp"
#include "sdkconfig.h"

class LGFX : public lgfx::LGFX_Device
{
public:
  lgfx::Panel_CVBS _panel_instance;

  LGFX(void)
  {
    {                                      
       // Configure display panel control settings
      auto cfg = _panel_instance.config(); // Gets the structure for display panel settings.

      // SONY ECX336C res: 640x400
      // https://github.com/lovyan03/LovyanGFX/blob/develop/doc/Panel_CVBS.md

      // Set output resolution;
      cfg.memory_width = AV_WIDTH_OG;//600;  // Output resolution width, OG 240
      cfg.memory_height = AV_HEIGHT_OG;//400; // Output resolution height, OG 160

      // Set the actual resolution to use; OG 208x128
      cfg.panel_width = AV_WIDTH;  // The actual width to be used (set a value equal to or smaller than memory_width)
      cfg.panel_height = AV_HEIGHT; // Height actually used (Set the same value as memory_height or a smaller value)

      // Set display position offset amount;
      cfg.offset_x = AV_SAFEZONE/2; // Amount to shift the display position to the right (initial value 0)
      cfg.offset_y = AV_SAFEZONE/2; // Amount to shift the display position downward (initial value 0)

      _panel_instance.config(cfg);

    /*
      Usually you specify the same value for memory_width and panel_width and use offset_x = 0 . ;
      If you want to prevent the display at the edge of the screen from being hidden outside the screen, set the value of panel_width smaller than memory_width and adjust the left/right position with offset_x. ;
      For example, if panel_width is set to 32 less than memory_width, setting offset_x to 16 will center the left and right positions. ;
      Adjust the vertical direction (memory_height, panel_height, offset_y) as needed. ;
    */
    
    }

    {
      auto cfg = _panel_instance.config_detail();

      // Set output signal type;
      // cfg.signal_type = cfg.signal_type_t::NTSC;
      cfg.signal_type = cfg.signal_type_t::NTSC_J;
      // cfg.signal_type = cfg.signal_type_t::PAL;
      // cfg.signal_type = cfg.signal_type_t::PAL_M;
      // cfg.signal_type = cfg.signal_type_t::PAL_N;

      // Set output destination GPIO number;
      cfg.pin_dac = 26; // DACを使用するため、 25 または 26 のみが選択できます;

      // Setting PSRAM Memory Allocation;
      cfg.use_psram = 2; // 0=no PSRAM used / 1=half PSRAM and half SRAM / 2=full PSRAM;

      // Sets the amplitude strength of the output signal;
      cfg.output_level = 128; // Initial value 128
      // Increase the value if the signal is attenuated due to reasons such as the GPIO has a protection resistor. ;
      // * M5StackCore2 recommends 200 because GPIO has protection resistance. ;

      // Sets the amplitude strength of the chroma signal;
      cfg.chroma_level = 128; // Initial value 128
      // Lowering the number will reduce saturation, and 0 will be black and white. 
      // Increasing the value increases the saturation;

      _panel_instance.config_detail(cfg);
    }

    setPanel(&_panel_instance);
  }
};