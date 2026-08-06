#include "bsp_gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define RELAY_PIN   GPIO_NUM_26

// KY-019 relay modules are typically active-LOW:
// writing 0 (LOW) energizes the relay (turns the load ON)
// writing 1 (HIGH) de-energizes it (turns the load OFF)

void app_main(void)
{
    BSP_GPIO_Init(RELAY_PIN, BSP_GPIO_MODE_OUTPUT);
    BSP_GPIO_Write(RELAY_PIN, 1);  // start OFF (safe default)

    while (1) {
        BSP_GPIO_Write(RELAY_PIN, 0);  // relay ON
        vTaskDelay(pdMS_TO_TICKS(2000));

        BSP_GPIO_Write(RELAY_PIN, 1);  // relay OFF
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}