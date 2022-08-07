project(bsp_test)

add_library(${PROJECT_NAME})

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    ${APP_INTERFACE_LIB_NAME}
)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/app_main.cpp
)

build_image("bsp" ${PROJECT_NAME})