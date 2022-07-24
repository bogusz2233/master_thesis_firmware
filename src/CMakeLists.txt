#[[###############################################
    Link libraries into executable.
    args:
        arg[0]      - Name of exectuable file.
        arg[1...N]  - List of libraries to link
#]]###############################################
function(build_image IMAGE_NAME ...)
    set(LIBRARIES_LIST ${ARGV})
    list(POP_FRONT LIBRARIES_LIST)
    set(IMAGE_OUT_NAME ${IMAGE_NAME}${EXECTUABLE_SUFFIX})

    message("Building image: [ ${IMAGE_NAME} ]")

    add_executable(${IMAGE_OUT_NAME})

    target_sources(
        ${IMAGE_OUT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/main.cpp
    )

    target_link_libraries(
        ${IMAGE_OUT_NAME}
        PRIVATE
        ${PLATFORM_LIB_NAME}
        ${DRIVERS_LIB_NAME}
        freertos
        ${LIBRARIES_LIST}
    )

    ## platform 
    if(COMMAND build_image_platform_depended)
        build_image_platform_depended(${IMAGE_OUT_NAME})
    endif()

endfunction()

add_subdirectory(config)
add_subdirectory(libs)
add_subdirectory(platform)
add_subdirectory(drivers)
add_subdirectory(apps)