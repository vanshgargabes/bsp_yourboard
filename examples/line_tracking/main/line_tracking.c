#include <stdio.h>
#include "bsp_gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define IR_PIN   GPIO_NUM_14   // KY-033 digital output, typically active-LOW

void app_main(void)
{
    BSP_GPIO_Init(IR_PIN, BSP_GPIO_MODE_INPUT);

    while (1) {
        int detected = (BSP_GPIO_Read(IR_PIN) == 0);   // active-LOW: LOW = obstacle/line detected

        printf("IR sensor: %s\n", detected ? "DETECTED" : "clear");

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}