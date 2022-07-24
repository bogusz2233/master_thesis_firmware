cmake_minimum_required(VERSION 3.23)

set(PLATFORM_LIB_NAME   "platform")
set(DRIVERS_LIB_NAME    "drivers")

add_subdirectory(toolchains)
add_subdirectory(targets)

if(NOT DEFINED TARGET)
    print_out_available_targets()
    message(FATAL_ERROR "\"TARGET\" variable not defined!")
endif()

if(NOT EXISTS ${TARGETS_DIR}/${TARGET})
    print_out_available_targets()
    message(FATAL_ERROR "TARGET: \"${TARGET}\" not exist")
endif()

include(${TARGETS_DIR}/${TARGET}/CMakeLists.txt)

project(master_thesis_firmware CXX ASM C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

add_subdirectory(externals)
add_subdirectory(src)
