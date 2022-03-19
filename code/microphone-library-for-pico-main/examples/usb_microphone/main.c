/*
 * Copyright (c) 2021 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 * 
 * This examples creates a USB Microphone device using the TinyUSB
 * library and captures data from a PDM microphone using a sample
 * rate of 16 kHz, to be sent the to PC.
 * 
 * The USB microphone code is based on the TinyUSB audio_test example.
 * 
 * https://github.com/hathach/tinyusb/tree/master/examples/device/audio_test
 */

#include "pico/pdm_microphone.h"
#include "blink.pio.h"
//#include "usb_microphone.h"
#include "hardware/clocks.h"
#include "tusb_config.h"

#ifndef SAMPLE_RATE
#define SAMPLE_RATE ((CFG_TUD_AUDIO_EP_SZ_IN / 2) - 1) * 1000
#endif

#ifndef SAMPLE_BUFFER_SIZE
#define SAMPLE_BUFFER_SIZE ((CFG_TUD_AUDIO_EP_SZ_IN/2) - 1)
#endif


// configuration
// 4 microphones, 0 - 3
// GPIOs: 4, 10, 24, 25 
#define num_mics 4
const int mic_pins[num_mics] = {4, 10, 24, 25};

// variables
uint16_t sample_buffer[num_mics][SAMPLE_BUFFER_SIZE];

// callback functions
void on_pdm_samples_ready(int);
//void on_usb_microphone_tx_ready();

void blink_pin_forever(PIO pio, uint sm, uint offset, uint pin, uint freq) {
    blink_program_init(pio, sm, offset, pin);
    pio_sm_set_enabled(pio, sm, true);

    printf("Blinking pin %d at %d Hz\n", pin, freq);
    pio->txf[sm] = clock_get_hz(clk_sys) / (2 * freq);
}

int main(void)
{
  //init the USB debug
  printf("Starting...");
  stdio_init_all();
  printf("Waiting...");
  sleep_ms(5000);
  printf("Started.");

  // initialize and start the PDM microphone array
  for (uint i = 0; i < num_mics; i++){
      //make a config struct for the current mic
        struct pdm_microphone_config curr_config = {
          .gpio_data = mic_pins[i],
          .gpio_clk = 11,
          .pio = pio0,
          .pio_sm = i,
          .sample_rate = SAMPLE_RATE,
          .sample_buffer_size = SAMPLE_BUFFER_SIZE,
        };

      printf("Configuring microphone: %d", i);

      //check if we are at the last mic in the list. If so, make the next mic the master that starts the others and runs the clock
      if (i == (num_mics - 1)){
          printf("Master mic creating...\n");
          pdm_microphone_init(&curr_config, 1, i);
      } else{
          printf("Slave mic creating...\n");
          pdm_microphone_init(&curr_config, 0, i);
      }

      //start that microphone
      pdm_microphone_set_samples_ready_handler(on_pdm_samples_ready, i);
      pdm_microphone_start(i);
    }

  //now that all mics configured and ready, start the array in sync
  pdm_start_mic_array();


  // initialize the USB microphone interface
  //usb_microphone_init();
  //usb_microphone_set_tx_ready_handler(on_usb_microphone_tx_ready);

  // enable to make LED blink
#if 0
  // start blink program 
  PIO pio = pio0;
  uint offset = pio_add_program(pio, &blink_program);
  printf("Loaded program at %d\n", offset);
  blink_pin_forever(pio, 1, offset, 25, 1);
#endif 

  while (1) {
    // run the USB microphone task continuously
    //usb_microphone_task();
    sleep_ms(10);
  }

  return 0;
}

void on_pdm_samples_ready(int id)
{
  // Callback from library when all the samples in the library
  // internal sample buffer are ready for reading.
  //
  // Read new samples into local buffer.
//  printf("got audio sample from mic: %d\n\n", id);
//  if (id == (num_mics - 1)){
//      printf("---detected final mic\n");
//      //pdm_microphone_read(sample_buffer, SAMPLE_BUFFER_SIZE, id);
//  }
    //pdm_microphone_read(sample_buffer[id], SAMPLE_BUFFER_SIZE, id);
    printf("MIC %d DATA: \n", id);
    for (int i = 0; i < SAMPLE_BUFFER_SIZE; i++){
        //printf("--- %d", sample_buffer[id][i]);
        uint16_t this_thing = sample_buffer[id][i];
    }
    printf("\n");
}

//void on_usb_microphone_tx_ready()
//{
//  // Callback from TinyUSB library when all data is ready
//  // to be transmitted.
//  //
//  // Write local buffer to the USB microphone
//  usb_microphone_write(sample_buffer, sizeof(sample_buffer));
//}
