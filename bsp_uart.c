#include "bsp_uart.h"
#include "freertos/FreeRTOS.h"

#define BSP_UART_BUF_SIZE  1024

void BSP_UART_Init(uart_port_t port, int tx_pin, int rx_pin, int baud_rate)
{
    uart_config_t uart_config = {
        .baud_rate = baud_rate,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    uart_param_config(port, &uart_config);
    uart_set_pin(port, tx_pin, rx_pin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(port, BSP_UART_BUF_SIZE * 2, 0, 0, NULL, 0);
}

int BSP_UART_Write(uart_port_t port, const uint8_t *data, size_t len)
{
    return uart_write_bytes(port, (const char *)data, len);
}

int BSP_UART_Read(uart_port_t port, uint8_t *buf, size_t max_len, uint32_t timeout_ms)
{
    return uart_read_bytes(port, buf, max_len, pdMS_TO_TICKS(timeout_ms));
}