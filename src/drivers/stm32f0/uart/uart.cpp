#include "drivers_manager.h"
#include "stm32f0xx_hal.h"
#include "uart.h"
#include <algorithm>
#include <stdarg.h>

namespace drivers {

/**
 * @brief Iniatilize UART.
 *
 * @return int
 */
int Uart::Init() {
    if (config.instance == nullptr) return Status::NULLPTR;

    if (!AllocateSemaphoresAndCirBuffer()) return Status::OUT_OF_MEMORY;
    if (!EnableClock()) return Status::IO_ERROR;
    if (!PeriphInit()) return Status::IO_ERROR;
    if (!RegisterIrq()) return Status::IO_ERROR;

    // Start receiving
    config.instance->CR1 = config.instance->CR1 | USART_CR1_RXNEIE;

    return Status::SUCCESS;
}

int Uart::Write(const void *data, int size) {
    if (data == nullptr) return Status::NULLPTR;

    const auto *begin  = reinterpret_cast<const uint8_t *>(data);
    const uint8_t *end = begin + size;

    auto send_byte     = [this](uint8_t byte) {
        xSemaphoreTake(tx_empty, pdMS_TO_TICKS(config.timeout_ms));
        config.instance->TDR = byte;
        config.instance->CR1 = config.instance->CR1 | USART_CR1_TXEIE;
    };

    if (xSemaphoreTake(lock, pdMS_TO_TICKS(config.timeout_ms)) != pdPASS) return Status::TIMEOUT;
    std::for_each(begin, end, send_byte);
    xSemaphoreGive(lock);

    return Status::SUCCESS;
}

int Uart::Read(void *data, int size) {
    if (data == nullptr) return Status::NULLPTR;
    int data_read;

    auto *data_output = reinterpret_cast<uint8_t *>(data);

    // uxSemaphoreGetCount
    for (data_read = 0; data_read < size; data_read++) {
        if (c_buffer_empty(rx_buffer)) {
            xSemaphoreTake(rx_data_available, pdMS_TO_TICKS(config.timeout_ms));
            if (c_buffer_empty(rx_buffer)) break;
        }

        data_output[data_read] = c_buffer_pop(rx_buffer);
        data_output++;
    }

    return data_read;
}

void Uart::Handle() {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if ((config.instance->ISR & USART_ISR_TXE) && (config.instance->CR1 & USART_CR1_TXEIE)) {
        config.instance->CR1 = config.instance->CR1 & ~USART_CR1_TXEIE;
        xSemaphoreGiveFromISR(tx_empty, &xHigherPriorityTaskWoken);
    }

    if (config.instance->ISR & USART_ISR_RXNE) {
        uint8_t data = config.instance->RDR;
        c_buffer_push(rx_buffer, data);
        xSemaphoreGiveFromISR(rx_data_available, &xHigherPriorityTaskWoken);
    }
}

inline bool Uart::AllocateSemaphoresAndCirBuffer() {
    lock = xSemaphoreCreateMutex();
    if (lock == nullptr) return false;

    tx_empty = xSemaphoreCreateBinary();
    if (tx_empty == nullptr) return false;

    rx_data_available = xSemaphoreCreateBinary();
    if (rx_data_available == nullptr) return false;

    rx_buffer = c_buffer_create(config.rx_buffer_size);
    if (rx_buffer == nullptr) return false;

    return true;
}

inline bool Uart::EnableClock() {
    if (config.instance == USART1) RCC->APB2ENR = RCC->APB2ENR | RCC_APB2ENR_USART1EN;
    else if (config.instance == USART2) RCC->APB1ENR = RCC->APB1ENR | RCC_APB1ENR_USART2EN;
    else if (config.instance == USART3) RCC->APB1ENR = RCC->APB1ENR | RCC_APB1ENR_USART3EN;
    else if (config.instance == USART4) RCC->APB1ENR = RCC->APB1ENR | RCC_APB1ENR_USART4EN;
    else return false;

    return true;
}

inline bool Uart::PeriphInit() {
    UART_HandleTypeDef uart_hal_handle{0};
    uart_hal_handle.Instance                    = config.instance;
    uart_hal_handle.Init.BaudRate               = config.baudrate;
    uart_hal_handle.Init.WordLength             = UART_WORDLENGTH_8B;
    uart_hal_handle.Init.StopBits               = UART_STOPBITS_1;
    uart_hal_handle.Init.Parity                 = UART_PARITY_NONE;
    uart_hal_handle.Init.Mode                   = UART_MODE_TX_RX;
    uart_hal_handle.Init.HwFlowCtl              = UART_HWCONTROL_NONE;
    uart_hal_handle.Init.OverSampling           = UART_OVERSAMPLING_8;
    uart_hal_handle.Init.OneBitSampling         = UART_ONE_BIT_SAMPLE_DISABLE;
    uart_hal_handle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

    return HAL_UART_Init(&uart_hal_handle) == HAL_OK;
}

inline bool Uart::RegisterIrq() {
    Driver *nvic = driver_manager.GetDriver(Major::NVIC_HANDLER, config.nvic_minor);
    if (nvic == nullptr) return false;

    IrqHandler *irq_handler = this;
    return nvic->Ioctl(Command::NVIC_REGISTER_IRQ, IRQn_Type::USART3_4_IRQn, irq_handler) == Status::SUCCESS;
}

} // namespace drivers
