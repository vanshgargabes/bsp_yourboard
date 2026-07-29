#include "bsp_gpio.h"

#define BSP_MAX_GPIO_PINS  40

static uint8_t gpio_state[BSP_MAX_GPIO_PINS] = {0};

void BSP_GPIO_Init(gpio_num_t pin, bsp_gpio_mode_t mode)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = 1ULL << pin,
        .intr_type = GPIO_INTR_DISABLE,
    };

    switch (mode) {
        case BSP_GPIO_MODE_OUTPUT:
            io_conf.mode = GPIO_MODE_OUTPUT;
            io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
            io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
            break;
        case BSP_GPIO_MODE_INPUT:
            io_conf.mode = GPIO_MODE_INPUT;
            io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
            io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
            break;
        case BSP_GPIO_MODE_INPUT_PULLUP:
            io_conf.mode = GPIO_MODE_INPUT;
            io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
            io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
            break;
        case BSP_GPIO_MODE_INPUT_PULLDOWN:
            io_conf.mode = GPIO_MODE_INPUT;
            io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
            io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
            break;
    }

    gpio_config(&io_conf);
    gpio_state[pin] = 0;
}

void BSP_GPIO_Write(gpio_num_t pin, int level)
{
    gpio_set_level(pin, level);
    gpio_state[pin] = level ? 1 : 0;
}

int BSP_GPIO_Read(gpio_num_t pin)
{
    return gpio_get_level(pin);
}

void BSP_GPIO_Toggle(gpio_num_t pin)
{
    gpio_state[pin] = !gpio_state[pin];
    gpio_set_level(pin, gpio_state[pin]);
}