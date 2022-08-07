#include "driver.h"
#include "nvic.h"

static drivers::Nvic _nvic;
drivers::Driver &nvic = _nvic;
