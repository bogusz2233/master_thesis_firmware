target_include_directories(
    ${DRIVERS_LIB_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(
    ${DRIVERS_LIB_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/gpio.cpp
)

add_config_file(drivers/gpio)