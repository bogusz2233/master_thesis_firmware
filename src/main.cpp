#include "drivers_manager.h"
#include "platform.h"

int main() {
    platform::Init();
    driver_manager.InitDrivers(drivers::InitStage::BeforeSystemBoot);

    while (true) {
        /* code */
    }

    return 0;
}