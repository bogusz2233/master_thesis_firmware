#include "stm32f0xx_hal.h"

extern void xPortSysTickHandler( void );

void SysTick_Handler(void){
     HAL_IncTick();
     xPortSysTickHandler();
}