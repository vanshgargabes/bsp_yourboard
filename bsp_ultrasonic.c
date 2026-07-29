#include "bsp_ultrasonic.h"
#include "bsp_gpio.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void BSP_Ultrasonic_Init(gpio_num_t trig_pin, gpio_num_t echo_pin)
{
    BSP_GPIO_Init(trig_pin, BSP_GPIO_MODE_OUTPUT);
    BSP_GPIO_Init(echo_pin, BSP_GPIO_MODE_INPUT);
    BSP_GPIO_Write(trig_pin, 0);
}

float BSP_Ultrasonic_ReadDistanceCM(gpio_num_t trig_pin, gpio_num_t echo_pin)
{
    // Send 10us trigger pulse
    BSP_GPIO_Write(trig_pin, 1);
    esp_rom_delay_us(10);
    BSP_GPIO_Write(trig_pin, 0);

    // Wait for echo to go high (with timeout)
    int64_t timeout_start = esp_timer_get_time();
    while (BSP_GPIO_Read(echo_pin) == 0) {
        if (esp_timer_get_time() - timeout_start > 30000) return -1.0f; // 30ms timeout
    }

    int64_t pulse_start = esp_timer_get_time();

    // Wait for echo to go low (with timeout)
    while (BSP_GPIO_Read(echo_pin) == 1) {
        if (esp_timer_get_time() - pulse_start > 30000) return -1.0f;
    }

    int64_t pulse_end = esp_timer_get_time();
    int64_t pulse_duration_us = pulse_end - pulse_start;

    // Speed of sound: 343 m/s -> 0.0343 cm/us, divide by 2 for round trip
    float distance_cm = (pulse_duration_us * 0.0343f) / 2.0f;
    return distance_cm;
}