#include "bsp_dht11.h"
#include "bsp_gpio.h"
#include "esp_rom_sys.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static int wait_for_level(gpio_num_t pin, int level, int timeout_us)
{
    int64_t start = esp_timer_get_time();
    while (BSP_GPIO_Read(pin) != level) {
        if (esp_timer_get_time() - start > timeout_us) return -1;
    }
    return 0;
}

int BSP_DHT11_Read(gpio_num_t pin, bsp_dht11_data_t *out)
{
    uint8_t data[5] = {0};

    // Send start signal: pull low >=18ms, then release
    BSP_GPIO_Init(pin, BSP_GPIO_MODE_OUTPUT);
    BSP_GPIO_Write(pin, 0);
    vTaskDelay(pdMS_TO_TICKS(20));
    BSP_GPIO_Write(pin, 1);
    esp_rom_delay_us(30);

    // Switch to input to read sensor's response
    BSP_GPIO_Init(pin, BSP_GPIO_MODE_INPUT_PULLUP);

    // Sensor pulls low ~80us, then high ~80us (response signal)
    if (wait_for_level(pin, 0, 100) != 0) return -1;
    if (wait_for_level(pin, 1, 100) != 0) return -1;
    if (wait_for_level(pin, 0, 100) != 0) return -1;

    // Read 40 bits (5 bytes)
    for (int i = 0; i < 40; i++) {
        if (wait_for_level(pin, 1, 100) != 0) return -1;

        int64_t high_start = esp_timer_get_time();
        if (wait_for_level(pin, 0, 100) != 0) return -1;
        int64_t high_duration = esp_timer_get_time() - high_start;

        data[i / 8] <<= 1;
        if (high_duration > 40) {
            data[i / 8] |= 1;  // long pulse (~70us) = bit 1, short (~26-28us) = bit 0
        }
    }

    // Verify checksum
    uint8_t checksum = data[0] + data[1] + data[2] + data[3];
    if (checksum != data[4]) return -1;

    out->humidity_percent = (float)data[0];
    out->temperature_c    = (float)data[2];

    return 0;
}