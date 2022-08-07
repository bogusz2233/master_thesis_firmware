#pragma once

namespace drivers {

enum class Command {
    // RCC:
    RCC_ENABLE_CLOCK,
    RCC_DISABLE_CLOCK,

    // GPIO:
    GPIO_PIN_SET,
    GPIO_PIN_GET,

    // NVIC:
    NVIC_REGISTER_IRQ,
};

enum Status {
    SUCCESS               = 0,
    TIMEOUT               = -1,
    IO_ERROR              = -2,
    IVALID_ARGUMENT       = -3,
    NOT_IMPLEMENTED       = -4,
    NULLPTR               = -5,
    COMMAND_NOT_SUPPORTED = -6,
    OUT_OF_RANGE          = -7,
    OUT_OF_MEMORY         = -8,
};

class Driver {
  public:
    virtual ~Driver(){};
    virtual int Init() = 0;
    virtual int Write(const void *data, int size);
    virtual int Read(void *data, int size);
    virtual int Ioctl(Command cmd, ...);
};

} // namespace drivers
