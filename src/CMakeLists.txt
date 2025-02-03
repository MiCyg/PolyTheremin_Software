
add_executable(${PROJECT_NAME}
    main.c
)

target_include_directories(${PROJECT_NAME} PRIVATE
    # ${CMAKE_CURRENT_LIST_DIR}
	${FREERTOS_CFG_DIRECTORY}
)

target_link_libraries(${PROJECT_NAME} 
	pico_stdlib 
	comlib
    FreeRTOS-Kernel-Heap4 
    )


pico_set_program_name(${PROJECT_NAME} ${PROJECT_NAME})
pico_set_program_version(${PROJECT_NAME} ${VERSION_NUMBER})

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(${PROJECT_NAME} 1)
# pico_enable_stdio_usb(${PROJECT_NAME} 1)

pico_add_extra_outputs(${PROJECT_NAME})