target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${FREERTOS_DIR}/portable/ThirdParty/GCC/Posix
)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
    ${FREERTOS_DIR}/portable/ThirdParty/GCC/Posix/port.c
)