#include "bsp_gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_PIN   GPIO_NUM_2

void app_main(void)
{
    BSP_GPIO_Init(LED_PIN, BSP_GPIO_MODE_OUTPUT);
    while (1) {
        BSP_GPIO_Toggle(LED_PIN);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}