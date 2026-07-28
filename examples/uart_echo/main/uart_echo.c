#include "bsp_uart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define UART_PORT   UART_NUM_2
#define TX_PIN      17
#define RX_PIN      16
#define BAUD_RATE   115200

void app_main(void)
{
    BSP_UART_Init(UART_PORT, TX_PIN, RX_PIN, BAUD_RATE);

    uint8_t rx_buf[128];
    while (1) {
        int len = BSP_UART_Read(UART_PORT, rx_buf, sizeof(rx_buf), 1000);
        if (len > 0) {
            BSP_UART_Write(UART_PORT, rx_buf, len);  // echo back
        }
    }
}