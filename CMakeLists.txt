idf_component_register(
    SRCS "bsp_gpio.c" "bsp_uart.c" "bsp_ultrasonic.c"
    INCLUDE_DIRS "include"
    REQUIRES esp_driver_gpio esp_driver_uart esp_timer
)