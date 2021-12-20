/*
 * Copyright (c) 2021 Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 * 
 */

#include <stdlib.h>
#include <string.h>

#include "hardware/clocks.h"
#include "hardware/dma.h"
#include "hardware/irq.h"

#include "OpenPDM2PCM/OpenPDMFilter.h"

#include "pdm_microphone.pio.h"

#include "pico/pdm_microphone.h"

#define PDM_DECIMATION       64
#define PDM_RAW_BUFFER_COUNT 2

static struct {
    struct pdm_microphone_config config;
    int dma_channel;
    uint8_t* raw_buffer[PDM_RAW_BUFFER_COUNT];
    volatile int raw_buffer_write_index;
    volatile int raw_buffer_read_index;
    uint raw_buffer_size;
    uint dma_irq;
    TPDMFilter_InitStruct filter;
    uint16_t filter_volume;
    pdm_samples_ready_handler_t samples_ready_handler;
} pdm_mic;

static void pdm_dma_handler();

int pdm_microphone_init(const struct pdm_microphone_config* config) {
    memset(&pdm_mic, 0x00, sizeof(pdm_mic));
    memcpy(&pdm_mic.config, config, sizeof(pdm_mic.config));

    if (config->sample_buffer_size % (config->sample_rate / 1000)) {
        return -1;
    }

    pdm_mic.raw_buffer_size = config->sample_buffer_size * (PDM_DECIMATION / 8);

    for (int i = 0; i < PDM_RAW_BUFFER_COUNT; i++) {
        pdm_mic.raw_buffer[i] = malloc(pdm_mic.raw_buffer_size);
        if (pdm_mic.raw_buffer[i] == NULL) {
            pdm_microphone_deinit();

            return -1;   
        }
    }

    pdm_mic.dma_channel = dma_claim_unused_channel(true);
    if (pdm_mic.dma_channel < 0) {
        pdm_microphone_deinit();

        return -1;
    }

    uint pio_sm_offset = pio_add_program(config->pio, &pdm_microphone_data_program);

    float clk_div = clock_get_hz(clk_sys) / (config->sample_rate * PDM_DECIMATION * 4.0);

    pdm_microphone_data_init(
        config->pio,
        config->pio_sm,
        pio_sm_offset,
        clk_div,
        config->gpio_data,
        config->gpio_clk
    );

    dma_channel_config dma_channel_cfg = dma_channel_get_default_config(pdm_mic.dma_channel);

    channel_config_set_transfer_data_size(&dma_channel_cfg, DMA_SIZE_8);
    channel_config_set_read_increment(&dma_channel_cfg, false);
    channel_config_set_write_increment(&dma_channel_cfg, true);
    channel_config_set_dreq(&dma_channel_cfg, pio_get_dreq(config->pio, config->pio_sm, false));

    pdm_mic.dma_irq = DMA_IRQ_0;

    dma_channel_configure(
        pdm_mic.dma_channel,
        &dma_channel_cfg,
        pdm_mic.raw_buffer[0],
        &config->pio->rxf[config->pio_sm],
        pdm_mic.raw_buffer_size,
        false
    );

    pdm_mic.filter.Fs = config->sample_rate;
    pdm_mic.filter.LP_HZ = config->sample_rate / 2;
    pdm_mic.filter.HP_HZ = 10;
    pdm_mic.filter.In_MicChannels = 1;
    pdm_mic.filter.Out_MicChannels = 1;
    pdm_mic.filter.Decimation = PDM_DECIMATION;
    pdm_mic.filter.MaxVolume = 64;
    pdm_mic.filter.Gain = 16;

    pdm_mic.filter_volume = pdm_mic.filter.MaxVolume;
}

void pdm_microphone_deinit() {
    for (int i = 0; i < PDM_RAW_BUFFER_COUNT; i++) {
        if (pdm_mic.raw_buffer[i]) {
            free(pdm_mic.raw_buffer[i]);

            pdm_mic.raw_buffer[i] = NULL;
        }
    }

    if (pdm_mic.dma_channel > -1) {
        dma_channel_unclaim(pdm_mic.dma_channel);

        pdm_mic.dma_channel = -1;
    }
}

int pdm_microphone_start() {
    irq_set_enabled(pdm_mic.dma_irq, true);
    irq_set_exclusive_handler(pdm_mic.dma_irq, pdm_dma_handler);

    if (pdm_mic.dma_irq == DMA_IRQ_0) {
        dma_channel_set_irq0_enabled(pdm_mic.dma_channel, true);
    } else if (pdm_mic.dma_irq == DMA_IRQ_1) {
        dma_channel_set_irq1_enabled(pdm_mic.dma_channel, true);
    } else {
        return -1;
    }

    Open_PDM_Filter_Init(&pdm_mic.filter);

    pio_sm_set_enabled(
        pdm_mic.config.pio,
        pdm_mic.config.pio_sm,
        true
    );

    pdm_mic.raw_buffer_write_index = 0;
    pdm_mic.raw_buffer_read_index = 0;

    dma_channel_transfer_to_buffer_now(
        pdm_mic.dma_channel,
        pdm_mic.raw_buffer[0],
        pdm_mic.raw_buffer_size
    );

    pio_sm_set_enabled(
        pdm_mic.config.pio,
        pdm_mic.config.pio_sm,
        true
    );
}

void pdm_microphone_stop() {
    pio_sm_set_enabled(
        pdm_mic.config.pio,
        pdm_mic.config.pio_sm,
        false
    );

    dma_channel_abort(pdm_mic.dma_channel);

    if (pdm_mic.dma_irq == DMA_IRQ_0) {
        dma_channel_set_irq0_enabled(pdm_mic.dma_channel, false);
    } else if (pdm_mic.dma_irq == DMA_IRQ_1) {
        dma_channel_set_irq1_enabled(pdm_mic.dma_channel, false);
    }

    irq_set_enabled(pdm_mic.dma_irq, false);
}

static void pdm_dma_handler() {
    // clear IRQ
    if (pdm_mic.dma_irq == DMA_IRQ_0) {
        dma_hw->ints0 = (1u << pdm_mic.dma_channel);
    } else if (pdm_mic.dma_irq == DMA_IRQ_1) {
        dma_hw->ints1 = (1u << pdm_mic.dma_channel);
    }

    // get the current buffer index
    pdm_mic.raw_buffer_read_index = pdm_mic.raw_buffer_write_index;

    // get the next capture index to send the dma to start
    pdm_mic.raw_buffer_write_index = (pdm_mic.raw_buffer_write_index + 1) % PDM_RAW_BUFFER_COUNT;

    // give the channel a new buffer to write to and re-trigger it
    dma_channel_transfer_to_buffer_now(
        pdm_mic.dma_channel,
        pdm_mic.raw_buffer[pdm_mic.raw_buffer_write_index],
        pdm_mic.raw_buffer_size
    );

    if (pdm_mic.samples_ready_handler) {
        pdm_mic.samples_ready_handler();
    }
}

void pdm_microphone_set_samples_ready_handler(pdm_samples_ready_handler_t handler) {
    pdm_mic.samples_ready_handler = handler;
}

void pdm_microphone_set_filter_max_volume(uint8_t max_volume) {
    pdm_mic.filter.MaxVolume = max_volume;
}

void pdm_microphone_set_filter_gain(uint8_t gain) {
    pdm_mic.filter.Gain = gain;
}

void pdm_microphone_set_filter_volume(uint16_t volume) {
    pdm_mic.filter_volume = volume;
}

int pdm_microphone_read(int16_t* buffer, size_t samples) {
    int filter_stride = (pdm_mic.filter.Fs / 1000);
    samples = (samples / filter_stride) * filter_stride;

    if (samples > pdm_mic.config.sample_buffer_size) {
        samples = pdm_mic.config.sample_buffer_size;
    }

    if (pdm_mic.raw_buffer_write_index == pdm_mic.raw_buffer_read_index) {
        return 0;
    }

    uint8_t* in = pdm_mic.raw_buffer[pdm_mic.raw_buffer_read_index];
    int16_t* out = buffer;

    pdm_mic.raw_buffer_read_index++;

    for (int i = 0; i < samples; i += filter_stride) {
#if PDM_DECIMATION == 64
        Open_PDM_Filter_64(in, out, pdm_mic.filter_volume, &pdm_mic.filter);
#elif PDM_DECIMATION == 128
        Open_PDM_Filter_128(in, out, pdm_mic.filter_volume, &pdm_mic.filter);
#else
        #error "Unsupported PDM_DECIMATION value!"
#endif

        in += filter_stride * (PDM_DECIMATION / 8);
        out += filter_stride;
    }

    return samples;
}
