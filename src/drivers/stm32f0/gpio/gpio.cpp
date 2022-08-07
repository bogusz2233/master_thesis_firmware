#include "gpio.h"
#include <algorithm>
#include <stdarg.h>

namespace drivers {

/**
 * @brief Initialize GPIO array.
 *
 * @retval Status::NULLPTR GPIO pointer equals nullptr.
 * @retval Status::SUCCESS GPIO initialization success.
 */
int Gpio::Init() {
    lock = xSemaphoreCreateMutex();
    if (lock == nullptr) return Status::OUT_OF_MEMORY;

    for (const GpioPortConfig &pin : config.ports_config) {
        if (pin.port == nullptr) return Status::NULLPTR;

        if (!EnablePortClock(pin.port)) return Status::IO_ERROR;

        GPIO_InitTypeDef gpio_init{
            .Pin       = pin.pin_number,
            .Mode      = pin.mode,
            .Pull      = pin.pull,
            .Speed     = pin.speed,
            .Alternate = pin.alternate,
        };
        HAL_GPIO_Init(pin.port, &gpio_init);

        SetupInitialPinState(pin);
    }

    return Status::SUCCESS;
}

/**
 * @brief Additional commands send to GPIO.
 *
 * Suported cmd:
 *  - Command::GPIO_PIN_SET
 *  - Command::GPIO_PIN_GET
 *
 * @param cmd   Commands to execute.
 * @param ...   Arguments to commands.
 * @return int  Error status.
 */
int Gpio::Ioctl(Command cmd, ...) {
    int status_code;
    va_list args;
    va_start(args, cmd);

    switch (cmd) {
    case Command::GPIO_PIN_SET: {
        auto pin_index = va_arg(args, uint32_t);
        auto state     = static_cast<bool>(va_arg(args, int));
        status_code    = PinSet(pin_index, state);
    } break;

    case Command::GPIO_PIN_GET: {
        auto pin_index = va_arg(args, uint32_t);
        status_code    = PinGet(pin_index);
    }

    default:
        status_code = Status::COMMAND_NOT_SUPPORTED;
        break;
    }

    va_end(args);
    return status_code;
}

/**
 * @brief Enable clock for GPIOx.
 *
 * @param port      PORT pointer.
 * @retval true     Clock enabled.
 * @retval false    Can't enable clock.
 */
inline bool Gpio::EnablePortClock(const GPIO_TypeDef *port) {
    if (port == GPIOA) RCC->AHBENR = RCC->AHBENR | RCC_AHBENR_GPIOAEN;
    else if (port == GPIOB) RCC->AHBENR = RCC->AHBENR | RCC_AHBENR_GPIOBEN;
    else if (port == GPIOC) RCC->AHBENR = RCC->AHBENR | RCC_AHBENR_GPIOCEN;
    else if (port == GPIOD) RCC->AHBENR = RCC->AHBENR | RCC_AHBENR_GPIODEN;
    else if (port == GPIOE) RCC->AHBENR = RCC->AHBENR | RCC_AHBENR_GPIOEEN;
    else if (port == GPIOF) RCC->AHBENR = RCC->AHBENR | RCC_AHBENR_GPIOFEN;
    else return false;

    return true;
}

/**
 * @brief GPIO set initial pin state.
 *
 * @param pin PIN index
 */
inline void Gpio::SetupInitialPinState(const GpioPortConfig &pin) {
    if (pin.initial_state == GpioInialState::SET) HAL_GPIO_WritePin(pin.port, pin.pin_number, GPIO_PIN_SET);
    if (pin.initial_state == GpioInialState::RESET) HAL_GPIO_WritePin(pin.port, pin.pin_number, GPIO_PIN_RESET);
}

/**
 * @brief Change pin output state.
 *
 * @param pin_index Pin index.
 * @param pin_state New output state.
 * @return operation status (Status).
 */
inline int Gpio::PinSet(uint32_t pin_index, bool pin_state) {
    if (pin_index >= config.ports_config.size()) return Status::OUT_OF_RANGE;

    GPIO_PinState pin_set_flag = pin_state ? GPIO_PIN_SET : GPIO_PIN_RESET;
    const GpioPortConfig &pin  = config.ports_config[pin_index];

    if (xSemaphoreTake(lock, pdMS_TO_TICKS(config.timeout_ms)) != pdPASS) {
        return Status::TIMEOUT;
    }
    HAL_GPIO_WritePin(pin.port, pin.pin_number, pin_set_flag);
    xSemaphoreGive(lock);

    return Status::SUCCESS;
}

/**
 * @brief Get pin input state.
 *
 * @param   pin_index               Pin index.
 *
 * @retval  Status::OUT_OF_RANGE    Can't find pin with this index.
 * @retval  1                       Pin state input high.
 * @retval  0                       Pin state input low.
 */
inline int Gpio::PinGet(uint32_t pin_index) {
    if (pin_index >= config.ports_config.size()) return Status::OUT_OF_RANGE;
    const GpioPortConfig &pin = config.ports_config[pin_index];

    if (xSemaphoreTake(lock, pdMS_TO_TICKS(config.timeout_ms)) != pdPASS) return Status::TIMEOUT;
    GPIO_PinState state = HAL_GPIO_ReadPin(pin.port, pin.pin_number);
    xSemaphoreGive(lock);

    return state == GPIO_PinState::GPIO_PIN_SET;
}

} // namespace drivers
