#include "driver.h"

namespace drivers {
int Driver::Write(const void *data, int size) { return Status::NOT_IMPLEMENTED; }
int Driver::Read(void *data, int size) { return Status::NOT_IMPLEMENTED; }
int Driver::Ioctl(Command cmd, ...) { return Status::NOT_IMPLEMENTED; }

} // namespace drivers
