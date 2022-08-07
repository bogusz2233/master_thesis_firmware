message("ARM added")
set(CMAKE_SYSTEM_NAME       Generic)
set(CMAKE_SYSTEM_PROCESSOR  Arm)

set(CROSS_TARGET_TRIPLET "arm-none-eabi-")

set(CMAKE_C_COMPILER    ${CROSS_TARGET_TRIPLET}gcc)
set(CMAKE_CXX_COMPILER  ${CROSS_TARGET_TRIPLET}g++)
set(CMAKE_ASM_COMPILER  ${CMAKE_C_COMPILER})
set(CMAKE_OBJCOPY       ${CROSS_TARGET_TRIPLET}objcopy)
set(CMAKE_SIZE_UTIL     ${CROSS_TARGET_TRIPLET}size)
set(CMAKE_OBJDUMP       ${CROSS_TARGET_TRIPLET}objdump)

add_link_options(
    --specs=nosys.specs
    --specs=nano.specs
    -lc
    -lm
    -Wl,--gc-sections 
    -Wl,--print-memory-usage
    -Wl,--start-group 
    -Wl,--end-group
)

add_compile_options(
    $<$<CONFIG:Debug>:-Og>
    $<$<CONFIG:Debug>:-g3>
    -ffunction-sections
    -fdata-sections 
    -mthumb
    --specs=nano.specs
    -ffunction-sections 
    -fdata-sections
    -fstack-usage
)
