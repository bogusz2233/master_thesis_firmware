set(CMAKE_TOOLCHAIN_FILE    ${TOOLCHAIN_DIR}/arm-none-eabi-gcc.cmake)
set(EXECTUABLE_SUFFIX       .elf)
set(PLATFORM                stm32f0)
set(CONFIG                  stm32f0_v0_1)

add_compile_options(
    -mcpu=cortex-m0
    -mfloat-abi=soft
)

add_link_options(
    -mcpu=cortex-m0
)

add_compile_definitions(
    STM32F072xB
    USE_HAL_DRIVER
)