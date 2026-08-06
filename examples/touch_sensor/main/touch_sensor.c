#include <stdio.h>
#include "bsp_gpio.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TOUCH_PIN           GPIO_NUM_13
#define POLL_DELAY_MS        10
#define MIN_STATE_DURATION_MS  150   // ignore changes faster than this

void app_main(void)
{
    BSP_GPIO_Init(TOUCH_PIN, BSP_GPIO_MODE_INPUT);

    int reported_state = BSP_GPIO_Read(TOUCH_PIN);
    int64_t last_change_time = esp_timer_get_time();

    while (1) {
        int raw = BSP_GPIO_Read(TOUCH_PIN);
        int64_t now = esp_timer_get_time();

        if (raw != reported_state &&
            (now - last_change_time) >= (MIN_STATE_DURATION_MS * 1000)) {
            reported_state = raw;
            last_change_time = now;
            printf("Touch state: %s\n", reported_state ? "TOUCHED" : "released");
        }

        vTaskDelay(pdMS_TO_TICKS(POLL_DELAY_MS));
    }
}