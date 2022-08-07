#include "gpio.h"
#include "gpio_config.h"
#include "stm32f0xx_hal.h"

using namespace drivers;

const static GpioPortConfig gpio_ports_config[]{
    [GpioPinName::LED_U] = GPIO_OUTPUT_PP(GPIOC, GPIO_PIN_6, GPIO_SPEED_FREQ_LOW, GpioInialState::RESET),
    [GpioPinName::LED_L] = GPIO_OUTPUT_PP(GPIOC, GPIO_PIN_8, GPIO_SPEED_FREQ_LOW, GpioInialState::RESET),
    [GpioPinName::LED_D] = GPIO_OUTPUT_PP(GPIOC, GPIO_PIN_7, GPIO_SPEED_FREQ_LOW, GpioInialState::RESET),
    [GpioPinName::LED_R] = GPIO_OUTPUT_PP(GPIOC, GPIO_PIN_9, GPIO_SPEED_FREQ_LOW, GpioInialState::RESET),
};

const GpioConfig gpio_config{
    .ports_config = gpio_ports_config,
    .timeout_ms   = 500,
};

static Gpio _gpio(gpio_config);
Driver &gpio = _gpio;