#include <stdio.h>
#include "bsp_gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#define VIBRATION_PIN   GPIO_NUM_14

static QueueHandle_t vibration_evt_queue = NULL;

static void IRAM_ATTR vibration_isr_handler(void *arg)
{
    uint32_t pin = (uint32_t)arg;
    xQueueSendFromISR(vibration_evt_queue, &pin, NULL);
}

void app_main(void)
{
    BSP_GPIO_Init(VIBRATION_PIN, BSP_GPIO_MODE_INPUT);

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