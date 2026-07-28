#pragma once
#include "driver/uart.h"

void BSP_UART_Init(uart_port_t port, int tx_pin, int rx_pin, int baud_rate);
int  BSP_UART_Write(uart_port_t port, const uint8_t *data, size_t len);
int  BSP_UART_Read(uart_port_t port, uint8_t *buf, size_t max_len, uint32_t timeout_ms);