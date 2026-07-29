#include "bsp_gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_PIN   GPIO_NUM_2

void app_main(void)
{
    BSP_GPIO_Init(LED_PIN, BSP_GPIO_MODE_OUTPUT);
    while (1) {
        BSP_GPIO_Write(LED_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(1000));
        BSP_GPIO_Write(LED_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}