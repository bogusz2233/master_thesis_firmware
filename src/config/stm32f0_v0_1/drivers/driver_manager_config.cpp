#include "drivers_manager.h"

extern drivers::Driver &rcc;

static drivers::Node nodes[]{
    ADD_DRIVER_NODE(drivers::Major::RCC, 0, drivers::InitStage::BeforeSystemBoot, rcc),
    ADD_DRIVER_NODE(drivers::Major::RCC, 1, drivers::InitStage::BeforeSystemBoot, rcc),
};

static const drivers::DriversManagerConfig drv_manager_config{
    .drivers_list = nodes,
};

drivers::DriversManager driver_manager(drv_manager_config);