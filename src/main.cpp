#include "FreeRTOS.h"
#include "app.h"
#include "drivers_manager.h"
#include "platform.h"
#include "task.h"
#include <assert.h>

static void SystemRun(void *);

int main() {
    platform::Init();
    driver_manager.InitDrivers(drivers::InitStage::BeforeSystemBoot);

    xTaskCreate(SystemRun, "System-Run", configMINIMAL_STACK_SIZE, nullptr, 1, nullptr);

    vTaskStartScheduler();

    while (true) {
        // Should never go there
    }

    return 0;
}

static void SystemRun(void *) {
    driver_manager.InitDrivers(drivers::InitStage::AfterSystemBoot);
    ApplicationMain();
}