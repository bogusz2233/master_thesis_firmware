#include "FreeRTOS.h"
#include "app.h"
#include "drivers_manager.h"
#include "platform.h"
#include "task.h"

const int LED_L = 1;

void ApplicationMain() {
    drivers::Driver *gpio = driver_manager.GetDriver(drivers::Major::GPIO, 0);
    assert(gpio != nullptr);

    while (true) {
        gpio->Ioctl(drivers::Command::GPIO_PIN_SET, LED_L, false);
        vTaskDelay(pdMS_TO_TICKS(250));
        gpio->Ioctl(drivers::Command::GPIO_PIN_SET, LED_L, true);
        platform::DelayMs(250);
    }
}