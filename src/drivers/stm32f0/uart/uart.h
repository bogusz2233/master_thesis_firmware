#pragma once

#include "circular_buffer.h"
#include "driver.h"
#include "irq_handler.h"
#include "stm32f0xx_hal.h"

#include "FreeRTOS.h"
#include "semphr.h"

namespace drivers {

struct UartConfig {
    USART_TypeDef *instance;
    uint16_t timeout_ms;
    uint32_t baudrate;
    uint8_t nvic_minor;
    uint16_t rx_buffer_size;
};

class Uart : public Driver, public IrqHandler {
  public:
    Uart(const UartConfig &uart_config) : config(uart_config) {}
    int Init() override;
    int Write(const void *data, int size) override;
    int Read(void *data, int size) override;
    void Handle() override;

  private:
    const UartConfig &config;
    SemaphoreHandle_t lock;              ///< Protect UART shared resources.
    SemaphoreHandle_t tx_empty;          ///< Signal that tx buffer is empty and next data can be sent.
    SemaphoreHandle_t rx_data_available; ///< New data received.

    cbuf_handle_t rx_buffer; ///< Circular buffer for incoming data.

    bool AllocateSemaphoresAndCirBuffer();
    bool EnableClock();
    bool PeriphInit();
    bool RegisterIrq();
};

} // namespace drivers