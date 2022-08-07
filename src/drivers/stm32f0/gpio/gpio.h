#pragma once

#include "driver.h"
#include "stm32f0xx_hal.h"
#include <span>
#include <stdint.h>

#include "FreeRTOS.h"
#include "semphr.h"
namespace drivers {

enum class GpioInialState {
    UNDEFINED,
    SET,
    RESET,
};

struct GpioPortConfig {
    GPIO_TypeDef *port;  // < GPIOx
    uint16_t pin_number; // < This parameter can be any value of @ref GPIO_pins
    uint32_t mode;       //< This parameter can be a value of @ref GPIO_mode
    uint32_t pull;       //< his parameter can be a value of @ref GPIO_pull
    uint32_t speed;      //< This parameter can be a value of @ref GPIO_speed
    GpioInialState initial_state = GpioInialState::UNDEFINED;
    uint32_t alternate; //< This parameter can be a value of @ref GPIOEx_Alternate_function_selection
};

constexpr GpioPortConfig GPIO_OUTPUT_PP(GPIO_TypeDef *port, uint16_t pin_number, uint32_t speed,
                                        GpioInialState initial = GpioInialState::UNDEFINED) {
    GpioPortConfig config{
        .port          = port,
        .pin_number    = pin_number,
        .mode          = GPIO_MODE_OUTPUT_PP,
        .pull          = GPIO_NOPULL,
        .speed         = speed,
        .initial_state = initial,
    };

    return config;
}

struct GpioConfig {
    const std::span<const GpioPortConfig> &ports_config;
    uint16_t timeout_ms;
};

class Gpio : public Driver {
  public:
    Gpio(const GpioConfig &gpio_config) : config(gpio_config) {}
    int Init() override;
    int Ioctl(Command cmd, ...) override;

  private:
    const GpioConfig &config;
    SemaphoreHandle_t lock;

    static bool EnablePortClock(const GPIO_TypeDef *port);
    void SetupInitialPinState(const GpioPortConfig &pin);
    int PinSet(uint32_t pin_index, bool pin_state);
    int PinGet(uint32_t pin_index);
};

} // namespace drivers