#pragma once
#include "driver/gpio.h"

void  BSP_Ultrasonic_Init(gpio_num_t trig_pin, gpio_num_t echo_pin);
float BSP_Ultrasonic_ReadDistanceCM(gpio_num_t trig_pin, gpio_num_t echo_pin);