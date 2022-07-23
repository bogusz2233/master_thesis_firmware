set(CMAKE_TOOLCHAIN_FILE    ${TOOLCHAIN_DIR}/arm-none-eabi-gcc.cmake)
set(EXECTUABLE_SUFFIX       .elf)
set(PLATFORM                stm32f0)

add_compile_options(
    -mcpu=cortex-m0
    -mfloat-abi=soft 
)

add_compile_definitions(
    STM32F072xB
    USE_HAL_DRIVER
)