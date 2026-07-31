#pragma once
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"

typedef struct {
    adc_oneshot_unit_handle_t adc_handle;
    adc_cali_handle_t cali_handle;
    bool cali_enabled;
} bsp_adc_channel_t;

// unit: ADC_UNIT_1 or ADC_UNIT_2, channel: ADC_CHANNEL_0..9 depending on pin
void BSP_ADC_Init(bsp_adc_channel_t *ctx, adc_unit_t unit, adc_channel_t channel);
int  BSP_ADC_ReadRaw(bsp_adc_channel_t *ctx, adc_channel_t channel);
int  BSP_ADC_ReadMillivolts(bsp_adc_channel_t *ctx, adc_channel_t channel);