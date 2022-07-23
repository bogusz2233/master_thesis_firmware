project(hal_stm32f0)

add_library(
    ${PROJECT_NAME}
    OBJECT
)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
    ${STM32F0XX_HAL_DIR}/Src/stm32f0xx_hal_gpio.c
    ${CMSIS_DEVICE_F0_DIR}/Source/Templates/gcc/startup_stm32f072xb.s
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMSIS_DEVICE_F0_DIR}/Include
    ${CMSIS_CORE_DIR}/Include
    ${STM32F0XX_HAL_DIR}/Inc
)
