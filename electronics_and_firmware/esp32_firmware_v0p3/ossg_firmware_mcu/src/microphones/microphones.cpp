#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "freertos/message_buffer.h"
#include "mbedtls/base64.h" //for encoding audio data to string
#include <math.h>
#include <cstring>

TickType_t lastTickTimeSend;
TickType_t lastTickTimeProc;

static const char *TAG = "MICROPHONES_OSSG";

// static const char *audioJsonTemplate = "%s"; //for testing

// Save audio from PDM microphone to SD Card in wav format

/* Microphone has following pins:
    VDD
    GND
    DOUT - connected to DIN I2S pin on ESP32
    CLK  - connected to WS I2S pin on ESP32
    LR   - not connected to ESP32. Microphone has internal pull-down to GND for this pin. */

#include <driver/i2s.h>

// place to pass audio around and save it
MessageBufferHandle_t audioMessageBuffer;
const size_t AUDIO_BUFFER_SIZE = 1024;// number of samples, each sample uint16_t
const size_t audioMessageBufferLen = (AUDIO_BUFFER_SIZE * sizeof(uint16_t)) + sizeof(size_t); // room for websocket buffer, room for one size_t for MessageBuffer overhead

static const char *audioJsonTemplate = "{\"MESSAGE_TYPE_LOCAL\" : \"AUDIO_CHUNK_DECRYPTED\", \"AUDIO_DATA\" : \"%s\"}";

// I2S perhiperhal number
#define I2S_CHANNEL I2S_NUM_0 // I2S_NUM_1 doesn't support PDM

// I2S pins
#define I2S_PIN_BIT_CLOCK I2S_PIN_NO_CHANGE // not used
#define I2S_PIN_WORD_SELECT 33              // OSSG_v0.3 built-in mic CLK
#define I2S_PIN_DATA_OUT I2S_PIN_NO_CHANGE  // not used
#define I2S_PIN_DATA_IN 32                  // OSSG_v0.3 built-in mic DATA_OUT

// I2S CONFIG PARAMS
#define SAMPLE_RATE 16000
const i2s_port_t I2S_PORT = I2S_NUM_0;
long total_read = 0;

/**************** Audio QUEUE HANDLER ***********************/
volatile uint8_t curr_audio_val = 0;
volatile bool audioSubscribed = false;
const size_t DMA_BUF_SIZE = 256; // number of samples, not number of bytes
const size_t DMA_BUF_CNT = 2;

int packet_count = 0;

bool I2S_Init()
{
    // pdm config for reading from left channel of PDM
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_PDM),
        .sample_rate = 16000,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_PCM_SHORT,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 4,
        .dma_buf_len = 1024,
        .use_apll = false,
        .tx_desc_auto_clear = false,
        .fixed_mclk = 0};

    i2s_pin_config_t pins = {
        .bck_io_num = I2S_PIN_BIT_CLOCK,
        .ws_io_num = I2S_PIN_WORD_SELECT,
        .data_out_num = I2S_PIN_DATA_OUT,
        .data_in_num = I2S_PIN_DATA_IN};

    if (i2s_driver_install(I2S_CHANNEL, &i2s_config, 0, NULL) != ESP_OK)
    {
        // Serial.println("i2s_driver_install() error");
        return false;
    }

    if (i2s_set_pin(I2S_NUM_0, &pins) != ESP_OK)
    {
        // Serial.println("i2s_set_pin() error");
        return false;
    }

    return true;
}

void I2S_Quit()
{
    if (i2s_driver_uninstall(I2S_CHANNEL) != ESP_OK)
    {
        ESP_LOGI(TAG, "i2s_driver_uninstall() error");
    }
}

#define min(a, b) (((a) < (b)) ? (a) : (b))

int i2s_read_custom(int16_t *samples, int count)
{
    int32_t raw_samples[256];
    int sample_index = 0;
    while (count > 0)
    {
        size_t bytes_read = 0;
        i2s_read(I2S_PORT, (void **)raw_samples, sizeof(int32_t) * min(count, 256), &bytes_read, portMAX_DELAY);
        int samples_read = bytes_read / sizeof(int32_t);
        for (int i = 0; i < samples_read; i++)
        {
            samples[sample_index] = (raw_samples[i] & 0xFFFFFFF0) >> 16;
            sample_index++;
            count--;
        }
    }
    return sample_index;
}

void setup_audio_buffer(){
    //initialize audio message buffer
    audioMessageBuffer = xMessageBufferCreate(audioMessageBufferLen * 4); //hold n message at once, where n is the constant multiplier
}

void microphone_stream(void *args)
{
    // Initialize I2S
    I2S_Init();

    // count how many bytes we read from I2S
    uint32_t bytes_read;

    ESP_LOGI(TAG, "Recording Started");

    //   uint8_t* buf = (uint8_t*)malloc(AUDIO_BUFFER_SIZE);
    int16_t *buf = (int16_t *)malloc(sizeof(uint16_t) * AUDIO_BUFFER_SIZE);
    while (true)
    {
        // Read data from microphone
        int samples_read = i2s_read_custom(buf, AUDIO_BUFFER_SIZE);
        int bytes_read = samples_read * sizeof(uint16_t);

        lastTickTimeProc = xTaskGetTickCount();

        if (samples_read != AUDIO_BUFFER_SIZE)
        {
            ESP_LOGE(TAG, "Bytes written error");
        }

        // send the bytes to the audio processor task
        size_t tx_bytes = xMessageBufferSend(audioMessageBuffer, buf, bytes_read, portMAX_DELAY);
    }

    // free the buffer memory
    free(buf);

    ESP_LOGI(TAG, "Recording finished");

    I2S_Quit();
}

// loop on receiving the latest audio chunk from the microphone and sending it to the WIS smart phone or cloud server
void sendAudioChunk(MessageBufferHandle_t websocketSendBuffer)
{
    audioSubscribed = true;
    while (true)
    {
        uint8_t *audioChunk = (uint8_t *)malloc(audioMessageBufferLen);
        int bytes_written = xMessageBufferReceive(audioMessageBuffer, audioChunk, audioMessageBufferLen, portMAX_DELAY);
        lastTickTimeSend = xTaskGetTickCount();
        
        if (bytes_written != 0)
        {
            if (audioSubscribed)
            {
                // base 64 encode data and send it to the server
                int b64EncodedAudioBufferLen = ((ceil(bytes_written / 3.0) * 4) + 1); // size increase due to inefficieny of base64 //+1 for padding, or something
                // printf("Tryna b64: %d\n", b64EncodedAudioBufferLen);
                unsigned char *b64EncodedAudio = (unsigned char *)malloc(b64EncodedAudioBufferLen);
                size_t encodedAudioActualLen;
                int b64res = mbedtls_base64_encode(b64EncodedAudio, b64EncodedAudioBufferLen, &encodedAudioActualLen, (unsigned char *)audioChunk, (size_t)bytes_written);
                if (b64res == 0)
                {
                    int jsonLength = b64EncodedAudioBufferLen + 256; // plus a bit for JSON extra info
                    //char jsonAudioPacket[jsonLength];
                    char * jsonAudioPacket = (char *)malloc(jsonLength);
                    snprintf(jsonAudioPacket, jsonLength, audioJsonTemplate, b64EncodedAudio);

                    //send data to be sent down websocket to ASP
                    size_t tx_bytes = xMessageBufferSend(websocketSendBuffer, jsonAudioPacket, strlen(jsonAudioPacket)+1, portMAX_DELAY);
                    free(jsonAudioPacket);
                }
                else {
                    ESP_LOGE(TAG, "Base 64 encoding failed.");
                    free(b64EncodedAudio);
                    continue;
                }
                free(b64EncodedAudio);
            }
            else
            {
                vTaskDelay(pdMS_TO_TICKS(250));
            }
        }
        free(audioChunk);
    }
}