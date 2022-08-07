project(freertos)

add_library(
    ${PROJECT_NAME}
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${FREERTOS_DIR}/include
)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
    ${FREERTOS_DIR}/portable/MemMang/heap_4.c
    ${FREERTOS_DIR}/tasks.c
    ${FREERTOS_DIR}/queue.c
    ${FREERTOS_DIR}/list.c
    ${FREERTOS_DIR}/timers.c

    ${CMAKE_CURRENT_SOURCE_DIR}/freertos.cpp
)

add_subdirectory(${PLATFORM})
add_config_file(libs/freertos)