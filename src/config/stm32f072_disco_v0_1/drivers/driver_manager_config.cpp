#include "drivers_manager.h"

extern drivers::Driver &rcc;
extern drivers::Driver &gpio;
extern drivers::Driver &nvic;

static drivers::Node nodes[]{
    ADD_DRIVER_NODE(drivers::Major::RCC, 0, drivers::InitStage::BeforeSystemBoot, rcc),
    ADD_DRIVER_NODE(drivers::Major::NVIC_HANDLER, 0, drivers::InitStage::BeforeSystemBoot, nvic),
    ADD_DRIVER_NODE(drivers::Major::GPIO, 0, drivers::InitStage::BeforeSystemBoot, gpio),
};

static const drivers::DriversManagerConfig drv_manager_config{
    .drivers_list = nodes,
};

drivers::DriversManager driver_manager(drv_manager_config);