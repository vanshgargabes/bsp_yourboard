#include <stdio.h>
#include "bsp_gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define DO_PIN      GPIO_NUM_27    // digital threshold trigger, polarity TBD — untested, no magnet available yet

void app_main(void)
{
    BSP_GPIO_Init(DO_PIN, BSP_GPIO_MODE_INPUT);

    while (1) {
        int level = BSP_GPIO_Read(DO_PIN);

        printf("Reed switch DO level: %d\n", level);

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}