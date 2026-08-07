#include <stdio.h>
#include "bsp_dht11.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define DHT11_PIN   GPIO_NUM_4

void app_main(void)
{
    bsp_dht11_data_t reading;

    while (1) {
        if (BSP_DHT11_Read(DHT11_PIN, &reading) == 0) {
            printf("Temp: %.1f C, Humidity: %.1f %%\n",
                   reading.temperature_c, reading.humidity_percent);
        } else {
            printf("DHT11 read failed\n");
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}