/*
 * Copyright (c) 2021 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 * 
 * 
 * This examples captures data from an analog microphone using a sample
 * rate of 8 kHz and prints the sample values over the USB serial
 * connection.
 */

#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/analog_microphone.h"
#include "tusb.h"

// configuration
const struct analog_microphone_config config = {
    // GPIO to use for input, must be ADC compatible (GPIO 26 - 28)
    .gpio = 26,

    // bias voltage of microphone in volts
    .bias_voltage = 1.25,

    // sample rate in Hz
    .sample_rate = 8000,

    // number of samples to buffer
    .sample_buffer_size = 256,
};

// variables
int16_t sample_buffer[256];
volatile int samples_read = 0;

void on_analog_samples_ready()
{
    // callback from library when all the samples in the library
    // internal sample buffer are ready for reading 
    samples_read = analog_microphone_read(sample_buffer, 256);
}

int main( void )
{
    // initialize stdio and wait for USB CDC connect
    stdio_init_all();
    while (!tud_cdc_connected()) {
        tight_loop_contents();
    }

    printf("hello analog microphone\n");

    // initialize the analog microphone
    if (analog_microphone_init(&config) < 0) {
        printf("analog microphone initialization failed!\n");
        while (1) { tight_loop_contents(); }
    }

    // set callback that is called when all the samples in the library
    // internal sample buffer are ready for reading
    analog_microphone_set_samples_ready_handler(on_analog_samples_ready);
    
    // start capturing data from the analog microphone
    if (analog_microphone_start() < 0) {
        printf("PDM microphone start failed!\n");
        while (1) { tight_loop_contents();  }
    }

    while (1) {
        // wait for new samples
        while (samples_read == 0) { tight_loop_contents(); }

        // store and clear the samples read from the callback
        int sample_count = samples_read;
        samples_read = 0;
        
        // loop through any new collected samples
        for (int i = 0; i < sample_count; i++) {
            printf("%d\n", sample_buffer[i]);
        }
    }

    return 0;
}
