#include "driver.h"

namespace drivers {

class Rcc : public Driver {
  public:
    int Init() override;
};

} // namespace drivers
