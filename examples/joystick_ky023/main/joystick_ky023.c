#include <stdio.h>
#include "bsp_adc.h"
#include "bsp_gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define VRX_UNIT     ADC_UNIT_1
#define VRX_CHANNEL  ADC_CHANNEL_6   // GPIO34
#define VRY_UNIT     ADC_UNIT_1
#define VRY_CHANNEL  ADC_CHANNEL_7   // GPIO35

#define SW_PIN       GPIO_NUM_25     // digital push button (active LOW)

void app_main(void)
{
    bsp_adc_channel_t vrx_ctx, vry_ctx;
    BSP_ADC_Init(&vrx_ctx, VRX_UNIT, VRX_CHANNEL);
    BSP_ADC_Init(&vry_ctx, VRY_UNIT, VRY_CHANNEL);

    BSP_GPIO_Init(SW_PIN, BSP_GPIO_MODE_INPUT_PULLUP);

    while (1) {
        int x_raw = BSP_ADC_ReadRaw(&vrx_ctx, VRX_CHANNEL);
        int y_raw = BSP_ADC_ReadRaw(&vry_ctx, VRY_CHANNEL);
        int x_mv  = BSP_ADC_ReadMillivolts(&vrx_ctx, VRX_CHANNEL);
        int y_mv  = BSP_ADC_ReadMillivolts(&vry_ctx, VRY_CHANNEL);
        int button_pressed = (BSP_GPIO_Read(SW_PIN) == 0);

        printf("X: raw=%d mv=%d | Y: raw=%d mv=%d | Button: %s\n",
               x_raw, x_mv, y_raw, y_mv,
               button_pressed ? "PRESSED" : "released");

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}