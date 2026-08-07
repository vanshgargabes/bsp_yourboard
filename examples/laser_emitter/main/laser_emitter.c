#include "bsp_gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LASER_PIN   GPIO_NUM_15

void app_main(void)
{
    BSP_GPIO_Init(LASER_PIN, BSP_GPIO_MODE_OUTPUT);
    while (1) {
        BSP_GPIO_Write(LASER_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(2000));
        BSP_GPIO_Write(LASER_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}