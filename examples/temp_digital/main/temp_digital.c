#include <stdio.h>
#include "bsp_adc.h"
#include "bsp_gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define AO_UNIT     ADC_UNIT_1
#define AO_CHANNEL  ADC_CHANNEL_6   // GPIO34 - analog temperature reading

#define DO_PIN      GPIO_NUM_27    // digital threshold trigger, active-HIGH

void app_main(void)
{
    bsp_adc_channel_t adc_ctx;
    BSP_ADC_Init(&adc_ctx, AO_UNIT, AO_CHANNEL);

    BSP_GPIO_Init(DO_PIN, BSP_GPIO_MODE_INPUT);

    while (1) {
        int temp_raw = BSP_ADC_ReadRaw(&adc_ctx, AO_CHANNEL);
        int temp_mv  = BSP_ADC_ReadMillivolts(&adc_ctx, AO_CHANNEL);

        int hw_triggered = (BSP_GPIO_Read(DO_PIN) == 1);        // active-HIGH, so 1 means not triggered, 0 means triggered

        printf("Temp sensor: raw=%d mv=%d | HW trigger: %s\n",
               temp_raw, temp_mv,
               hw_triggered ? "YES" : "no");

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}