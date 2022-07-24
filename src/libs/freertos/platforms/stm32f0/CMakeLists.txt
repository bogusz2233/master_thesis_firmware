target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${FREERTOS_DIR}/portable/GCC/ARM_CM0
)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
    ${FREERTOS_DIR}/portable/GCC/ARM_CM0/port.c

)