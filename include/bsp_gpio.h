#pragma once
#include "driver/gpio.h"

typedef enum {
    BSP_GPIO_MODE_OUTPUT,
    BSP_GPIO_MODE_INPUT,
    BSP_GPIO_MODE_INPUT_PULLUP,
    BSP_GPIO_MODE_INPUT_PULLDOWN,
} bsp_gpio_mode_t;

typedef void (*bsp_gpio_isr_callback_t)(void *arg);

void BSP_GPIO_Init(gpio_num_t pin, bsp_gpio_mode_t mode);
void BSP_GPIO_Write(gpio_num_t pin, int level);
int  BSP_GPIO_Read(gpio_num_t pin);
void BSP_GPIO_Toggle(gpio_num_t pin);

// Register an interrupt callback on a pin. edge: GPIO_INTR_POSEDGE, GPIO_INTR_NEGEDGE, or GPIO_INTR_ANYEDGE
void BSP_GPIO_AttachInterrupt(gpio_num_t pin, gpio_int_type_t edge, bsp_gpio_isr_callback_t callback, void *arg);