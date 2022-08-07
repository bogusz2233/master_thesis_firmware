project(hal_stm32f0)

add_library(
    ${PROJECT_NAME}
    STATIC
)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
    ${STM32F0XX_HAL_DIR}/Src/stm32f0xx_hal_gpio.c
    ${CMSIS_DEVICE_F0_DIR}/Source/Templates/gcc/startup_stm32f072xb.s

    ${STM32F0XX_HAL_DIR}/Src/stm32f0xx_hal.c
    ${STM32F0XX_HAL_DIR}/Src/stm32f0xx_hal_cortex.c
    ${STM32F0XX_HAL_DIR}/Src/stm32f0xx_hal_rcc.c
    ${STM32F0XX_HAL_DIR}/Src/stm32f0xx_hal_rcc_ex.c
    ${STM32F0XX_HAL_DIR}/Src/stm32f0xx_hal_tim.c
    ${STM32F0XX_HAL_DIR}/Src/stm32f0xx_hal_tim_ex.c
    ${STM32F0XX_HAL_DIR}/Src/stm32f0xx_hal_uart.c
    ${STM32F0XX_HAL_DIR}/Src/stm32f0xx_hal_uart_ex.c
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMSIS_DEVICE_F0_DIR}/Include
    ${CMSIS_CORE_DIR}/Include
    ${STM32F0XX_HAL_DIR}/Inc
)
