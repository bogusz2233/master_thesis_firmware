#[[###############################################
    Print out information about avaiable platforms.
#]]###############################################
function(print_out_available_configs)
    file(
        GLOB                FILE_LIST 
        LIST_DIRECTORIES    TRUE 
        RELATIVE               ${CMAKE_CURRENT_FUNCTION_LIST_DIR}
        ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/*
    )

    message("Available config:")
    foreach(FILE_ENT ${FILE_LIST})
        if(IS_DIRECTORY ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/${FILE_ENT})
            message("   * ${FILE_ENT}")
        endif()
    endforeach()
    
endfunction()

if(NOT DEFINED CONFIG)
print_out_available_configs()
    message(FATAL_ERROR "\"CONFIG\" variable not defined!")
endif()

if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${CONFIG})
print_out_available_configs()
    message(FATAL_ERROR "CONFIG: \"${CONFIG}\" not exist")
endif()

set(CONFIG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${CONFIG} PARENT_SCOPE)

function(add_config_file CONFIG_PATH)
    add_subdirectory(${CONFIG_DIR}/${CONFIG_PATH} ${CMAKE_CURRENT_BINARY_DIR}/config)
endfunction()
