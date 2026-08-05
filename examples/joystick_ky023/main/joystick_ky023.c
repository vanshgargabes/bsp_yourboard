#include <stdio.h>
#include "bsp_adc.h"
#include "bsp_gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define ADC_UNIT_USED  ADC_UNIT_1
#define VRX_CHANNEL    ADC_CHANNEL_6   // GPIO34
#define VRY_CHANNEL    ADC_CHANNEL_7   // GPIO35

#define SW_PIN         GPIO_NUM_25

void app_main(void)
{
    bsp_adc_channel_t adc_ctx;
    BSP_ADC_Init(&adc_ctx, ADC_UNIT_USED, VRX_CHANNEL);  // creates the unit + configures VRx channel

    // Configure the second channel on the SAME already-created unit — do NOT call BSP_ADC_Init again
    adc_oneshot_chan_cfg_t chan_config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12,
    };
    adc_oneshot_config_channel(adc_ctx.adc_handle, VRY_CHANNEL, &chan_config);

    BSP_GPIO_Init(SW_PIN, BSP_GPIO_MODE_INPUT_PULLUP);

    while (1) {
        int x_raw = BSP_ADC_ReadRaw(&adc_ctx, VRX_CHANNEL);
        int y_raw = BSP_ADC_ReadRaw(&adc_ctx, VRY_CHANNEL);
        int x_mv  = BSP_ADC_ReadMillivolts(&adc_ctx, VRX_CHANNEL);
        int button_pressed = (BSP_GPIO_Read(SW_PIN) == 0);

        printf("X: raw=%d mv=%d | Y: raw=%d | Button: %s\n",
               x_raw, x_mv, y_raw,
               button_pressed ? "PRESSED" : "released");

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}