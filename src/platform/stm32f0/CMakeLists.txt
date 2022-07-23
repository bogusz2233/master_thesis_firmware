

function(build_image_platform_depended IMAGE_NAME)
    message("STM32F0: ${LINKER_SCRIPT_PATH}")
    set(LINKER_SCRIPT_PATH  ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/linker/STM32F072RBTx_FLASH.ld)
 

    target_link_options(
        ${IMAGE_NAME}
        PRIVATE
        -T${LINKER_SCRIPT_PATH}
        -Wl,-Map=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${IMAGE_NAME}.map,--cref
    )
endfunction()

target_sources(
    ${PLATFORM_LIB_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/system_stm32f0xx.c
)

target_link_libraries(
    ${PLATFORM_LIB_NAME}
    PRIVATE
    hal_stm32f0
)