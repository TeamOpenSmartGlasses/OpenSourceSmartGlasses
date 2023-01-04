//static const char *TAG = "SDSPI";

#define MOUNT_POINT "/sdcard"

// #define PIN_NUM_MISO GPIO_NUM_37 
// #define PIN_NUM_MOSI GPIO_NUM_35
// #define PIN_NUM_CLK  GPIO_NUM_36
#define PIN_NUM_CS   GPIO_NUM_33
static sdmmc_card_t* sdcard;

bool init_sdspi()
{
    sdspi_device_config_t device_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    device_config.host_id = SPI2_HOST;
    device_config.gpio_cs = PIN_NUM_CS;  

    ESP_LOGI(TAG, "Initializing SD card");
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    host.slot = device_config.host_id;

    esp_vfs_fat_mount_config_t mount_config = 
    {
    #ifdef CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED
        .format_if_mount_failed = true,
    #else
        .format_if_mount_failed = false,
    #endif
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };

    //sdmmc_card_t* card;
    ESP_LOGI(TAG, "Mounting filesystem");
    esp_err_t ret = esp_vfs_fat_sdspi_mount(MOUNT_POINT, &host, &device_config, &mount_config, &sdcard);
    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount filesystem. "
                     "If you want the card to be formatted, set the CONFIG_EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig option.");
            return ESP_FAIL;
        } else {
            ESP_LOGE(TAG, "Failed to initialize the card (%s). "
                     "Make sure SD card lines have pull-up resistors in place.", esp_err_to_name(ret));
            return ESP_FAIL;
        }
        return ESP_FAIL;
    }
    ESP_LOGI(TAG, "Filesystem mounted");

    // Card has been initialized, print its properties
    sdmmc_card_print_info(stdout, sdcard);

    return ESP_OK;
}

