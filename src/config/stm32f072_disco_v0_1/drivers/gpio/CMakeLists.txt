target_sources(
    ${DRIVERS_LIB_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/gpio_config.cpp
)

target_include_directories(
    ${DRIVERS_LIB_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)