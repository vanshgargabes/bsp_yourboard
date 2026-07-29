#include <stdio.h>
#include "bsp_ultrasonic.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TRIG_PIN   GPIO_NUM_5
#define ECHO_PIN   GPIO_NUM_18

void app_main(void)
{
    BSP_Ultrasonic_Init(TRIG_PIN, ECHO_PIN);

    while (1) {
        float distance = BSP_Ultrasonic_ReadDistanceCM(TRIG_PIN, ECHO_PIN);
        if (distance >= 0) {
            printf("Distance: %.2f cm\n", distance);
        } else {
            printf("Ultrasonic read timeout\n");
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}