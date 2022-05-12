/*
 * Copyright (c) 2021 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 * 
 */

#ifndef _PICO_PDM_MICROPHONE_H_
#define _PICO_PDM_MICROPHONE_H_

#include "hardware/pio.h"

typedef void (*pdm_samples_ready_handler_t)(int);

struct pdm_microphone_config {
    uint gpio_data;
    uint gpio_clk;
    PIO pio;
    uint pio_sm;
    uint sample_rate;
    uint sample_buffer_size;
};

int pdm_microphone_init(const struct pdm_microphone_config* config, bool master_flag, int id_arg);
void pdm_microphone_deinit(int id);

int pdm_microphone_start(int id);
void pdm_start_mic_array();
void pdm_microphone_stop(int id);

void pdm_microphone_set_samples_ready_handler(pdm_samples_ready_handler_t handler, int id);
void pdm_microphone_set_filter_max_volume(uint8_t max_volume, int id);
void pdm_microphone_set_filter_gain(uint8_t gain, int id);
void pdm_microphone_set_filter_volume(uint16_t volume, int id);

int pdm_microphone_read(int16_t* buffer, size_t samples, int id);

#endif
