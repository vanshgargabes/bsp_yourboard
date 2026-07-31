#include <stdio.h>
#include "bsp_gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BUTTON_PIN   GPIO_NUM_0
#define LED_PIN      GPIO_NUM_2

void app_main(void)
{
    // Button wired to GND when pressed -> use internal pull-up, LOW = pressed
    BSP_GPIO_Init(BUTTON_PIN, BSP_GPIO_MODE_INPUT_PULLUP);
    BSP_GPIO_Init(LED_PIN, BSP_GPIO_MODE_OUTPUT);

    int last_state = 1;

    while (1) {
        int current_state = BSP_GPIO_Read(BUTTON_PIN);

        if (current_state == 0 && last_state == 1) {
            printf("Button pressed!\n");
            BSP_GPIO_Write(LED_PIN, 1);
        } else if (current_state == 1 && last_state == 0) {
            printf("Button released\n");
            BSP_GPIO_Write(LED_PIN, 0);
        }

        last_state = current_state;
        vTaskDelay(pdMS_TO_TICKS(20));  // simple debounce delay
    }
}