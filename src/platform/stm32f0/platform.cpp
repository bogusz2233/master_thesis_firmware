#include "platform.h"
#include "stm32f0xx_hal.h"
#include "stm32f0xx_hal_tim.h"
TIM_HandleTypeDef htim1;

namespace platform {

/**
 * @brief Initialize platform
 */
void Init() { HAL_Init(); }

/**
 * @brief Actively waiting time_ms ms.
 *
 * @param time_ms   Time in ms to wait for.
 */
void DelayMs(uint32_t time_ms) { HAL_Delay(time_ms); }

} // namespace platform
