set(TARGETS_DIR                     ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/images  PARENT_SCOPE)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/libs    PARENT_SCOPE)

function(print_out_available_targets)
    file(
        GLOB                FILE_LIST 
        LIST_DIRECTORIES    TRUE 
        RELATIVE               ${CMAKE_CURRENT_FUNCTION_LIST_DIR}
        ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/*
    )

    message("Available targets (-DTARGET=<target_name>):")
    foreach(FILE_ENT ${FILE_LIST})
        if(IS_DIRECTORY ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/${FILE_ENT})
            message("   * ${FILE_ENT}")
        endif()
    endforeach()
    

endfunction()
