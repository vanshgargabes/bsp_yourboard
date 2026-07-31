#pragma once
#include "driver/gpio.h"

typedef struct {
    float temperature_c;
    float humidity_percent;
} bsp_dht11_data_t;

// Returns 0 on success, -1 on timeout/checksum failure
int BSP_DHT11_Read(gpio_num_t pin, bsp_dht11_data_t *out);