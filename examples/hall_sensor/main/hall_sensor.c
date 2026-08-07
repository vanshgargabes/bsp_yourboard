#include <stdio.h>
#include "bsp_gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define HALL_SENSOR_PIN   GPIO_NUM_33

void app_main(void)
{
    // KY-003 pulls signal LOW when a magnetic field is detected,
    // HIGH otherwise (open-collector output) -> use internal pull-up.
    BSP_GPIO_Init(HALL_SENSOR_PIN, BSP_GPIO_MODE_INPUT_PULLUP);

    int last_state = 1;

    while (1) {
        int current_state = BSP_GPIO_Read(HALL_SENSOR_PIN);

        if (current_state == 0 && last_state == 1) {
            printf("Magnetic field detected!\n");
        } else if (current_state == 1 && last_state == 0) {
            printf("Magnetic field lost\n");
        }

        last_state = current_state;
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}