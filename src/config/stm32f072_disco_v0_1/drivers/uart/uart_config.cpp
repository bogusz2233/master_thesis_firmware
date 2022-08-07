#include "uart.h"

drivers::UartConfig uart3_config{
    .instance       = USART3,
    .timeout_ms     = 250,
    .baudrate       = 115600,
    .nvic_minor     = 0,
    .rx_buffer_size = 100,
};

static drivers::Uart _uart3(uart3_config);
drivers::Driver &uart3 = _uart3;