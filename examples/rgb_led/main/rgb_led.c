#include "bsp_gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define RED_PIN     GPIO_NUM_25
#define GREEN_PIN   GPIO_NUM_26
#define BLUE_PIN    GPIO_NUM_27

// Polarity TBD — most KY-016 modules are common-cathode (HIGH = ON),
// but common-anode variants exist (LOW = ON). Test and confirm before committing.

void set_color(int r, int g, int b)
{
    BSP_GPIO_Write(RED_PIN, r);
    BSP_GPIO_Write(GREEN_PIN, g);
    BSP_GPIO_Write(BLUE_PIN, b);
}

void app_main(void)
{
    BSP_GPIO_Init(RED_PIN, BSP_GPIO_MODE_OUTPUT);
    BSP_GPIO_Init(GREEN_PIN, BSP_GPIO_MODE_OUTPUT);
    BSP_GPIO_Init(BLUE_PIN, BSP_GPIO_MODE_OUTPUT);

    while (1) {
        set_color(1, 0, 0);   // Red
        vTaskDelay(pdMS_TO_TICKS(1000));

        set_color(0, 1, 0);   // Green
        vTaskDelay(pdMS_TO_TICKS(1000));

        set_color(0, 0, 1);   // Blue
        vTaskDelay(pdMS_TO_TICKS(1000));

        set_color(0, 0, 0);   // Off
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}