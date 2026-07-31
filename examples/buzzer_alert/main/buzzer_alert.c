#include <stdio.h>

void app_main(void)
{

}
#include "bsp_gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BUZZER_PIN   GPIO_NUM_15

void app_main(void)
{
    BSP_GPIO_Init(BUZZER_PIN, BSP_GPIO_MODE_OUTPUT);

    while (1) {
        // Beep pattern: on 200ms, off 800ms
        BSP_GPIO_Write(BUZZER_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(200));
        BSP_GPIO_Write(BUZZER_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(800));
    }
}