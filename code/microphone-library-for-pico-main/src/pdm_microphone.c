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
#include "pdm_microphone_slave.pio.h"

#include "pico/pdm_microphone.h"

#define PDM_DECIMATION       64
#define PDM_RAW_BUFFER_COUNT 2

typedef struct pdm_mic {
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
};

#define num_mics 4
//handle up to n mics in an array, can be made bigger, but to do so, dev will need to make new dma handler functions (see 4 almost identical functions at bottom of this file, and see the associated comment

struct pdm_mic pdm_mics[num_mics];

static void pdm_dma_handler();
//static void pdm_dma_handler_mic_zero();
//static void pdm_dma_handler_mic_one();
//static void pdm_dma_handler_mic_two();
//static void pdm_dma_handler_mic_three();

int pdm_microphone_init(const struct pdm_microphone_config* config, bool master, int id) {
    memset(&pdm_mics[id], 0x00, sizeof(struct pdm_mic));
    memcpy(&pdm_mics[id].config, config, sizeof(struct pdm_microphone_config));

    if (config->sample_buffer_size % (config->sample_rate / 1000)) {
        return -1;
    }

    pdm_mics[id].raw_buffer_size = config->sample_buffer_size * (PDM_DECIMATION / 8);

    for (int i = 0; i < PDM_RAW_BUFFER_COUNT; i++) {
        pdm_mics[id].raw_buffer[i] = malloc(pdm_mics[id].raw_buffer_size);
        if (pdm_mics[id].raw_buffer[i] == NULL) {
            pdm_microphone_deinit(id);

            return -1;   
        }
    }

    pdm_mics[id].dma_channel = dma_claim_unused_channel(true);
    if (pdm_mics[id].dma_channel < 0) {
        pdm_microphone_deinit(id);

        return -1;
    }

    float clk_div = clock_get_hz(clk_sys) / (config->sample_rate * PDM_DECIMATION * 4.0);

    //only start a master state machine program if we defined this as master
    if (master){
        uint pio_sm_offset = pio_add_program(config->pio, &pdm_microphone_data_program);
        pdm_microphone_data_init(
            config->pio,
            config->pio_sm,
            pio_sm_offset,
            clk_div,
            config->gpio_data,
            config->gpio_clk
        );
    } else {
        uint pio_sm_offset = pio_add_program(config->pio, &pdm_microphone_slave_data_program);
        pdm_microphone_slave_data_init(
            config->pio,
            config->pio_sm,
            pio_sm_offset,
            clk_div,
            config->gpio_data,
            config->gpio_clk
        );
    }

    dma_channel_config dma_channel_cfg = dma_channel_get_default_config(pdm_mics[id].dma_channel);

    channel_config_set_transfer_data_size(&dma_channel_cfg, DMA_SIZE_8);
    channel_config_set_read_increment(&dma_channel_cfg, false);
    channel_config_set_write_increment(&dma_channel_cfg, true);
    channel_config_set_dreq(&dma_channel_cfg, pio_get_dreq(config->pio, config->pio_sm, false));

    pdm_mics[id].dma_irq = DMA_IRQ_0;

    dma_channel_configure(
        pdm_mics[id].dma_channel,
        &dma_channel_cfg,
        pdm_mics[id].raw_buffer[0],
        &config->pio->rxf[config->pio_sm],
        pdm_mics[id].raw_buffer_size,
        false
    );

    pdm_mics[id].filter.Fs = config->sample_rate;
    pdm_mics[id].filter.LP_HZ = config->sample_rate / 2;
    pdm_mics[id].filter.HP_HZ = 10;
    pdm_mics[id].filter.In_MicChannels = 1;
    pdm_mics[id].filter.Out_MicChannels = 1;
    pdm_mics[id].filter.Decimation = PDM_DECIMATION;
    pdm_mics[id].filter.MaxVolume = 64;
    pdm_mics[id].filter.Gain = 16;

    pdm_mics[id].filter_volume = pdm_mics[id].filter.MaxVolume;
}

void pdm_microphone_deinit(int id) {
    for (int i = 0; i < PDM_RAW_BUFFER_COUNT; i++) {
        if (pdm_mics[id].raw_buffer[i]) {
            free(pdm_mics[id].raw_buffer[i]);

            pdm_mics[id].raw_buffer[i] = NULL;
        }
    }

    if (pdm_mics[id].dma_channel > -1) {
        dma_channel_unclaim(pdm_mics[id].dma_channel);

        pdm_mics[id].dma_channel = -1;
    }
}

int pdm_microphone_start(int id) {
    irq_set_enabled(pdm_mics[id].dma_irq, true);

    printf("Starting MIC: %d handler...\n", id);
    printf("This mic has dma_irq: %d", pdm_mics[id].dma_irq);
    printf("This mic has dma_channel: %d", pdm_mics[id].dma_channel);
    printf("setting handler...\n");
    //if (irq_get_exclusive_handler(pdm_mics[id].dma_irq == NULL)){ //if we haven't yet set the handler
    if (id == 0){ //if we haven't yet set the handler
        printf("WAS NULL, so set"); irq_set_exclusive_handler(pdm_mics[id].dma_irq, pdm_dma_handler);
    }

    printf("handler set\n");

    printf("enabling irq...\n");
    if (pdm_mics[id].dma_irq == DMA_IRQ_0) {
        dma_channel_set_irq0_enabled(pdm_mics[id].dma_channel, true);
    } else if (pdm_mics[id].dma_irq == DMA_IRQ_1) {
        dma_channel_set_irq1_enabled(pdm_mics[id].dma_channel, true);
    } else {
        return -1;
    }
    printf("irq enabled\n");

    printf("PDM filter init...");
    Open_PDM_Filter_Init(&pdm_mics[id].filter);
    printf("DONE PDM filter init...");

//    printf("piosmsetenabled...\n");
//    pio_sm_set_enabled(
//        pdm_mics[id].config.pio,
//        pdm_mics[id].config.pio_sm,
//        true
//    );
//    printf("piosmsetenabled DONE\n");

    pdm_mics[id].raw_buffer_write_index = 0;
    pdm_mics[id].raw_buffer_read_index = 0;

    printf("dma_channel_transfer_to_buffer_now...\n");
    dma_channel_transfer_to_buffer_now(
        pdm_mics[id].dma_channel,
        pdm_mics[id].raw_buffer[0],
        pdm_mics[id].raw_buffer_size
    );
    printf("dma_channel_transfer_to_buffer_now DONE\n");
}

//start all mics running together with clocks in sync
void pdm_start_mic_array(){
    uint32_t enable_mask = (1<<0) | (1<<1) | (1<<2) | (1<<3); //enable the first two, for now
    pio_enable_sm_mask_in_sync(pio0, enable_mask);
}

void pdm_microphone_stop(int id) {
    pio_sm_set_enabled(
        pdm_mics[id].config.pio,
        pdm_mics[id].config.pio_sm,
        false
    );

    dma_channel_abort(pdm_mics[id].dma_channel);

    if (pdm_mics[id].dma_irq == DMA_IRQ_0) {
        dma_channel_set_irq0_enabled(pdm_mics[id].dma_channel, false);
    } else if (pdm_mics[id].dma_irq == DMA_IRQ_1) {
        dma_channel_set_irq1_enabled(pdm_mics[id].dma_channel, false);
    }

    irq_set_enabled(pdm_mics[id].dma_irq, false);
}

void pdm_microphone_set_samples_ready_handler(pdm_samples_ready_handler_t handler, int id) {
    pdm_mics[id].samples_ready_handler = handler;
}

void pdm_microphone_set_filter_max_volume(uint8_t max_volume, int id) {
    pdm_mics[id].filter.MaxVolume = max_volume;
}

void pdm_microphone_set_filter_gain(uint8_t gain, int id) {
    pdm_mics[id].filter.Gain = gain;
}

void pdm_microphone_set_filter_volume(uint16_t volume, int id) {
    pdm_mics[id].filter_volume = volume;
}

int pdm_microphone_read(int16_t* buffer, size_t samples, int id) {
    int filter_stride = (pdm_mics[id].filter.Fs / 1000);
    samples = (samples / filter_stride) * filter_stride;

    if (samples > pdm_mics[id].config.sample_buffer_size) {
        samples = pdm_mics[id].config.sample_buffer_size;
    }

    if (pdm_mics[id].raw_buffer_write_index == pdm_mics[id].raw_buffer_read_index) {
        return 0;
    }

    uint8_t* in = pdm_mics[id].raw_buffer[pdm_mics[id].raw_buffer_read_index];
    int16_t* out = buffer;

    pdm_mics[id].raw_buffer_read_index++;

    for (int i = 0; i < samples; i += filter_stride) {
#if PDM_DECIMATION == 64
        Open_PDM_Filter_64(in, out, pdm_mics[id].filter_volume, &pdm_mics[id].filter);
#elif PDM_DECIMATION == 128
        Open_PDM_Filter_128(in, out, pdm_mics[id].filter_volume, &pdm_mics[id].filter);
#else
        #error "Unsupported PDM_DECIMATION value!"
#endif

        in += filter_stride * (PDM_DECIMATION / 8);
        out += filter_stride;
    }

    return samples;
}

static void pdm_dma_handler() {
    //which DMA channel raised the IRQ?
    int id = -1;
    for (int i = 0; i < num_mics; i++){
        if (dma_channel_get_irq0_status(pdm_mics[i].dma_channel)){
            id = i;
        }
    }
    printf("pdm_dma_handler, mic id: %d\n", id);

    // clear IRQ
    if (pdm_mics[id].dma_irq == DMA_IRQ_0) {
        dma_hw->ints0 = (1u << pdm_mics[id].dma_channel);
    } else if (pdm_mics[id].dma_irq == DMA_IRQ_1) {
        dma_hw->ints1 = (1u << pdm_mics[id].dma_channel);
    }
    
    //make sure we found the proper channel, if not, exit
    if (id == -1){
        return;
    }

    // get the current buffer index
    pdm_mics[id].raw_buffer_read_index = pdm_mics[id].raw_buffer_write_index;

    // get the next capture index to send the dma to start
    pdm_mics[id].raw_buffer_write_index = (pdm_mics[id].raw_buffer_write_index + 1) % PDM_RAW_BUFFER_COUNT;

    // give the channel a new buffer to write to and re-trigger it
    dma_channel_transfer_to_buffer_now(
        pdm_mics[id].dma_channel,
        pdm_mics[id].raw_buffer[pdm_mics[id].raw_buffer_write_index],
        pdm_mics[id].raw_buffer_size
    );

    if (pdm_mics[id].samples_ready_handler) {
        pdm_mics[id].samples_ready_handler(id);
    }
}
