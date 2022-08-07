
#include "nvic.h"
#include "string.h"
#include <stdarg.h>
#include <stdint.h>

extern uint32_t _isr_flash_start;

namespace drivers {

typedef void (*IrqHandleFunc_t)(void);

const int INTERUPT_OFFSET   = 16;
const int MAX_INTERUPTS_NUM = 32 + INTERUPT_OFFSET;
__attribute__((section(".isr_vector_ram"))) IrqHandleFunc_t vector_ram[MAX_INTERUPTS_NUM];
const auto *FLASH_ISR_VECTOR                       = reinterpret_cast<const IrqHandleFunc_t *>(&_isr_flash_start);
static IrqHandler *irq_handlers[MAX_INTERUPTS_NUM] = {nullptr};

/**
 * @brief Initialize NVIC.
 *
 * Initialize Nvic driver. Copy and move ISR VECTOR to ram.
 *
 * @return int
 */
int Nvic::Init() {
    lock = xSemaphoreCreateMutex();
    if (lock == nullptr) return Status::OUT_OF_MEMORY;

    // Copy ISR_VECTOR
    memcpy(vector_ram, FLASH_ISR_VECTOR, sizeof(vector_ram));

    // Change ISR_VECTOR
    __disable_irq();
    SYSCFG->CFGR1 = SYSCFG->CFGR1 | SYSCFG_CFGR1_MEM_MODE;
    __enable_irq();

    return Status::SUCCESS;
}

/**
 * @brief Send command to interact with driver.
 *
 * Suported cmd:
 *  - Command::NVIC_REGISTER_IRQ
 *
 * @param cmd   Command to execute.
 * @param ...   Command arguments.
 * @return int  Status.
 */
int Nvic::Ioctl(Command cmd, ...) {
    int status_code;
    va_list args;
    va_start(args, cmd);

    switch (cmd) {
    case Command::NVIC_REGISTER_IRQ: {
        auto irq_index   = static_cast<IRQn_Type>(va_arg(args, int));
        auto irq_handler = reinterpret_cast<IrqHandler *>(va_arg(args, void *));
        status_code      = RegisterIrq(irq_index, irq_handler);
    } break;

    default: {
        status_code = Status::COMMAND_NOT_SUPPORTED;
    } break;
    }

    return status_code;
}

/**
 * @brief Register new interrupt.
 *
 * @param irq_type  Interupt index.
 * @param handler   Interupt executer.
 * @return int      Status.
 */
inline int Nvic::RegisterIrq(IRQn_Type irq_type, IrqHandler *handler) {
    if (handler == nullptr) return Status::NULLPTR;

    if (xSemaphoreTake(lock, pdMS_TO_TICKS(250)) != pdPASS) {
        return Status::TIMEOUT;
    }

    __disable_irq();
    irq_handlers[irq_type + INTERUPT_OFFSET] = handler;
    vector_ram[irq_type + INTERUPT_OFFSET]   = IrqHandle;
    __enable_irq();

    HAL_NVIC_SetPriority(irq_type, 3, 0U);
    HAL_NVIC_EnableIRQ(irq_type);

    xSemaphoreGive(lock);

    return Status::SUCCESS;
}

/// @brief static function used to service interupts.
void Nvic::IrqHandle() {
    uint16_t irq_num = SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk;
    if (irq_handlers[irq_num] == nullptr) {
        return;
    }

    irq_handlers[irq_num]->Handle();
}

} // namespace drivers
