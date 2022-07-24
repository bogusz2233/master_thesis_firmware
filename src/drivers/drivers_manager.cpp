#include "drivers_manager.h"
#include <assert.h>

namespace drivers {

/**
 * @brief Construct a new Drivers Manager:: Drivers Manager object
 *
 * @param drv_manager_config Initial configuraiton of driver manager.
 */
DriversManager::DriversManager(const DriversManagerConfig &drv_manager_config) : config(drv_manager_config) {

    for (Node &node : config.drivers_list) {
        auto major = static_cast<uint32_t>(node.major);

        if (nodes[major] == nullptr) {
            nodes[major] = &node;
        } else {
            Node *node_tmp = nodes[major];
            // search for the last one
            while (node_tmp->next != nullptr) {
                node_tmp = node_tmp->next;
            }

            node_tmp->next = &node;
        }

        node.next = nullptr;
    }
}

/**
 * @brief Function that initilize Drivers.
 *
 * @param stage Stage when driver should be initialized.
 */
void DriversManager::InitDrivers(InitStage stage) {
    for (Node &node : config.drivers_list) {
        if (node.init_stage == stage) {
            int status = node.driver.Init();
            assert(status == Status::SUCCESS);
        }
    }
}

/**
 * @brief Get driver base on it major and minor numbers
 *
 * @param major Major number of driver descibing driver type.
 * @param minor Minor number of driver descirbing driver instance.
 *
 * @retval Driver*  pointer of driver.
 */
Driver *DriversManager::GetDriver(Major major, uint8_t minor) {
    auto major_tmp = static_cast<uint32_t>(major);
    if (major_tmp > static_cast<uint32_t>(Major::_DEVICE_MAJOR_COUNT)) return nullptr;
    if (nodes[major_tmp] == nullptr) return nullptr;

    Node *node = nodes[major_tmp];

    do {
        if (node->minor == minor) return &node->driver;
        node = node->next;
    } while (node != nullptr);

    return nullptr;
}

} // namespace drivers
