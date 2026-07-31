#include <stdio.h>
#include "bsp_adc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define ADC_UNIT_USED     ADC_UNIT_1
#define ADC_CHANNEL_USED  ADC_CHANNEL_6   // GPIO34 on most ESP32 devkits

void app_main(void)
{
    bsp_adc_channel_t adc_ctx;
    BSP_ADC_Init(&adc_ctx, ADC_UNIT_USED, ADC_CHANNEL_USED);

    while (1) {
        int raw = BSP_ADC_ReadRaw(&adc_ctx, ADC_CHANNEL_USED);
        int mv  = BSP_ADC_ReadMillivolts(&adc_ctx, ADC_CHANNEL_USED);

        printf("ADC raw: %d, Voltage: %d mV\n", raw, mv);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}