#include <stdio.h>
#include "bsp_gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define OBSTACLE_PIN   GPIO_NUM_14   // KY-032 digital output, typically active-LOW

void app_main(void)
{
    BSP_GPIO_Init(OBSTACLE_PIN, BSP_GPIO_MODE_INPUT);

    while (1) {
        int obstacle = (BSP_GPIO_Read(OBSTACLE_PIN) == 0);   // active-LOW: LOW = obstacle in range

        printf("Obstacle sensor: %s\n", obstacle ? "OBSTACLE DETECTED" : "clear");

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}