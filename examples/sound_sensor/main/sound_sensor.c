#include <stdio.h>
#include "bsp_adc.h"
#include "bsp_gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define AO_UNIT     ADC_UNIT_1
#define AO_CHANNEL  ADC_CHANNEL_6   // GPIO34 - analog sound level

#define DO_PIN      GPIO_NUM_27    // digital threshold trigger, active-LOW

#define SOUND_THRESHOLD_RAW   2850   // matches the module's own HW threshold (~2800-2900 observed)

void app_main(void)
{
    bsp_adc_channel_t adc_ctx;
    BSP_ADC_Init(&adc_ctx, AO_UNIT, AO_CHANNEL);

    BSP_GPIO_Init(DO_PIN, BSP_GPIO_MODE_INPUT);

    while (1) {
        int sound_raw = BSP_ADC_ReadRaw(&adc_ctx, AO_CHANNEL);
        int sound_mv  = BSP_ADC_ReadMillivolts(&adc_ctx, AO_CHANNEL);

        int hw_triggered = (BSP_GPIO_Read(DO_PIN) != 0);        // active-LOW: LOW = triggered
        int sw_triggered = (sound_raw < SOUND_THRESHOLD_RAW);   // same direction: below threshold = triggered

        printf("Sound level: raw=%d mv=%d | HW trigger: %s | SW trigger: %s\n",
               sound_raw, sound_mv,
               hw_triggered ? "YES" : "no",
               sw_triggered ? "YES" : "no");

        vTaskDelay(pdMS_TO_TICKS(300));
    }
}