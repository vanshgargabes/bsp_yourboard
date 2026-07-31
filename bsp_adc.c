#include "bsp_adc.h"
#include "esp_log.h"

static const char *TAG = "BSP_ADC";

void BSP_ADC_Init(bsp_adc_channel_t *ctx, adc_unit_t unit, adc_channel_t channel)
{
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = unit,
    };
    adc_oneshot_new_unit(&init_config, &ctx->adc_handle);

    adc_oneshot_chan_cfg_t chan_config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12,   // ~0-3.3V input range
    };
    adc_oneshot_config_channel(ctx->adc_handle, channel, &chan_config);

    // Try to set up calibration for millivolt conversion
    adc_cali_curve_fitting_config_t cali_config = {
        .unit_id = unit,
        .chan = channel,
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };

    esp_err_t ret = adc_cali_create_scheme_curve_fitting(&cali_config, &ctx->cali_handle);
    ctx->cali_enabled = (ret == ESP_OK);

    if (!ctx->cali_enabled) {
        ESP_LOGW(TAG, "ADC calibration not available, raw-only mode");
    }
}

int BSP_ADC_ReadRaw(bsp_adc_channel_t *ctx, adc_channel_t channel)
{
    int raw_value = 0;
    adc_oneshot_read(ctx->adc_handle, channel, &raw_value);
    return raw_value;
}

int BSP_ADC_ReadMillivolts(bsp_adc_channel_t *ctx, adc_channel_t channel)
{
    int raw_value = BSP_ADC_ReadRaw(ctx, channel);

    if (ctx->cali_enabled) {
        int voltage_mv = 0;
        adc_cali_raw_to_voltage(ctx->cali_handle, raw_value, &voltage_mv);
        return voltage_mv;
    }

    return -1;  // calibration unavailable
}