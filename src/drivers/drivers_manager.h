#pragma once

#include "driver.h"
#include <span>
#include <stdint.h>

namespace drivers {

enum class Major {
    RCC,
    GPIO,
    UART,
    NVIC_HANDLER,
    _DEVICE_MAJOR_COUNT,
};

enum class InitStage : uint8_t {
    BeforeSystemBoot,
    AfterSystemBoot,
};

struct Node {
    Major major;
    uint8_t minor;
    InitStage init_stage;
    Driver &driver;

    Node *next = nullptr;
};

constexpr Node ADD_DRIVER_NODE(Major major, uint8_t minor, InitStage init_stage, Driver &driver) {
    Node node{
        .major      = major,
        .minor      = minor,
        .init_stage = init_stage,
        .driver     = driver,
        .next       = nullptr,
    };

    return node;
}

struct DriversManagerConfig {
    std::span<Node> drivers_list;
};

class DriversManager {
  public:
    DriversManager(const DriversManagerConfig &drv_manager_config);
    void InitDrivers(InitStage stage);
    Driver *GetDriver(Major major, uint8_t minor);

  private:
    const DriversManagerConfig &config;
    Node *nodes[static_cast<uint32_t>(Major::_DEVICE_MAJOR_COUNT)] = {nullptr};
};

} // namespace drivers

extern drivers::DriversManager driver_manager;