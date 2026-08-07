#include <stdio.h>
#include "bsp_gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define CLK_PIN   GPIO_NUM_32
#define DT_PIN    GPIO_NUM_33
#define SW_PIN    GPIO_NUM_25

void app_main(void)
{
    BSP_GPIO_Init(CLK_PIN, BSP_GPIO_MODE_INPUT_PULLUP);
    BSP_GPIO_Init(DT_PIN, BSP_GPIO_MODE_INPUT_PULLUP);
    BSP_GPIO_Init(SW_PIN, BSP_GPIO_MODE_INPUT_PULLUP);

    int last_clk = BSP_GPIO_Read(CLK_PIN);
    int position = 0;
    int last_sw = 1;

    while (1) {
        int clk = BSP_GPIO_Read(CLK_PIN);
        int dt  = BSP_GPIO_Read(DT_PIN);
        int sw  = BSP_GPIO_Read(SW_PIN);

        if (clk != last_clk) {
            if (dt != clk) {
                position++;
            } else {
                position--;
            }
            printf("Position: %d\n", position);
        }
        last_clk = clk;

        if (sw == 0 && last_sw == 1) {
            printf("Button pressed!\n");
        }
        last_sw = sw;

        vTaskDelay(pdMS_TO_TICKS(5));
    }
}