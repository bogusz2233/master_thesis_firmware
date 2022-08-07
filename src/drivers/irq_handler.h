#pragma once

namespace drivers {
class IrqHandler {
  public:
    virtual ~IrqHandler(){};
    virtual void Handle() = 0;
};

} // namespace drivers
