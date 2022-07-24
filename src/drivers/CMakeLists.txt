add_library( ${DRIVERS_LIB_NAME} )

target_sources(
    ${DRIVERS_LIB_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/driver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers_manager.cpp
)

target_include_directories(
    ${DRIVERS_LIB_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    ${DRIVERS_LIB_NAME}
    PRIVATE
    ${PLATFORM_LIB_NAME}
)

add_config_file(drivers)

add_subdirectory(${PLATFORM}/rcc)
