#include <stdio.h>
#include "bsp_gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_timer.h"

#define VIBRATION_PIN     GPIO_NUM_14
#define DEBOUNCE_US       30000   // 30ms — tune to your sensor

static QueueHandle_t vibration_evt_queue = NULL;
static volatile int64_t last_isr_time = 0;

static void IRAM_ATTR vibration_isr_handler(void *arg)
{
    int64_t now = esp_timer_get_time();
    if (now - last_isr_time < DEBOUNCE_US) {
        return;  // ignore bounce/noise within debounce window
    }
    last_isr_time = now;

    uint32_t pin = (uint32_t)arg;
    xQueueSendFromISR(vibration_evt_queue, &pin, NULL);
}

void app_main(void)
{
    // Pull-up enabled: pin rests HIGH, sensor pulls it LOW when triggered.
    // If your sensor wiring is the opposite polarity, switch this to
    // BSP_GPIO_MODE_INPUT_PULLDOWN instead.
    BSP_GPIO_Init(VIBRATION_PIN, BSP_GPIO_MODE_INPUT_PULLUP);

    vibration_evt_queue = xQueueCreate(10, sizeof(uint32_t));

    BSP_GPIO_AttachInterrupt(VIBRATION_PIN, GPIO_INTR_ANYEDGE, vibration_isr_handler, (void *)VIBRATION_PIN);

    uint32_t pin;
    while (1) {
        if (xQueueReceive(vibration_evt_queue, &pin, portMAX_DELAY)) {
            int level = BSP_GPIO_Read(VIBRATION_PIN);
            printf("Vibration event! Level now: %d\n", level);
        }
    }
}