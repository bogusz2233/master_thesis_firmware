#include "drivers_manager.h"
#include "gpio_config.h"
#include "platform.h"
#include <assert.h>

int main() {
    platform::Init();
    driver_manager.InitDrivers(drivers::InitStage::BeforeSystemBoot);

    drivers::Driver *gpio = driver_manager.GetDriver(drivers::Major::GPIO, 0);
    assert(gpio != nullptr);

    while (true) {
        gpio->Ioctl(drivers::Command::GPIO_PIN_SET, drivers::GpioPinName::LED_D, true);
        gpio->Ioctl(drivers::Command::GPIO_PIN_SET, drivers::GpioPinName::LED_L, false);
        platform::DelayMs(250);
        gpio->Ioctl(drivers::Command::GPIO_PIN_SET, drivers::GpioPinName::LED_D, false);
        platform::DelayMs(250);
    }

    return 0;
}