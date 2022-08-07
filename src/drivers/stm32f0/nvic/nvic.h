#pragma once
#include "FreeRTOS.h"
#include "driver.h"
#include "irq_handler.h"
#include "semphr.h"
#include "stm32f0xx_hal.h"
#include <functional>

namespace drivers {

class Nvic : public Driver {
  public:
    int Init() override;
    int Ioctl(Command cmd, ...) override;

  private:
    SemaphoreHandle_t lock;
    int RegisterIrq(IRQn_Type irq_type, IrqHandler *handler);
    static void IrqHandle();
};

} // namespace drivers
