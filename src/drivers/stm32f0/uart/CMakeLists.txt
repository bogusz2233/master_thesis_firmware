target_include_directories(
    ${DRIVERS_LIB_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(
    ${DRIVERS_LIB_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/uart.cpp
)

target_link_libraries(
    ${DRIVERS_LIB_NAME}
    PRIVATE
    circular_buffer
)

add_config_file(drivers/uart)