add_library( 
    ${PLATFORM_LIB_NAME}
    OBJECT
)

target_include_directories(
    ${PLATFORM_LIB_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

#[[###############################################
    Print out information about avaiable platforms.
#]]###############################################
function(print_out_available_platforms)
    file(
        GLOB                FILE_LIST 
        LIST_DIRECTORIES    TRUE 
        RELATIVE               ${CMAKE_CURRENT_FUNCTION_LIST_DIR}
        ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/*
    )

    message("Available platforms:")
    foreach(FILE_ENT ${FILE_LIST})
        if(IS_DIRECTORY ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/${FILE_ENT})
            message("   * ${FILE_ENT}")
        endif()
    endforeach()
    
endfunction()

if(NOT DEFINED PLATFORM)
    print_out_available_platforms()
    message(FATAL_ERROR "\"PLATFORM\" variable not defined!")
endif()

if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${PLATFORM})
    print_out_available_platforms()
    message(FATAL_ERROR "PLATFORM: \"${PLATFORM}\" not exist")
endif()

add_subdirectory(${PLATFORM})
