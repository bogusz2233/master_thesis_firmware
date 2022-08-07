#pragma once

namespace drivers {
class IrqHandler {
  public:
    virtual ~IrqHandler(){};
    virtual int Handle() = 0;
};

} // namespace drivers
