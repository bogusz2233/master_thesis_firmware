add_library(
    ${APP_INTERFACE_LIB_NAME}
    INTERFACE
)

target_include_directories(
    ${APP_INTERFACE_LIB_NAME}
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    ${APP_INTERFACE_LIB_NAME}
    INTERFACE
    ${DRIVERS_LIB_NAME}
    freertos
    ${PLATFORM_LIB_NAME}
)

add_subdirectory(bsp)
