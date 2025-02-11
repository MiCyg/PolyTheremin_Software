project(freq_meas)

add_library(${PROJECT_NAME} STATIC freq_meas.c)
# pico_generate_pio_header(freq_meas ${CMAKE_CURRENT_LIST_DIR}/freq_meas.pio)
set_source_files_properties(freq_meas.c PROPERTIES COMPILE_FLAGS -fno-common)
target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC comlib)
target_link_libraries(${PROJECT_NAME} 
PUBLIC 
hardware_dma 
hardware_pwm
)

# target_compile_definitions(main PRIVATE GPIO_IRQ_CALLBACK_ORDER_PRIORITY=PICO_SHARED_IRQ_HANDLER_HIGHEST_ORDER_PRIORITY)
# target_compile_definitions(main PRIVATE GPIO_RAW_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY=PICO_SHARED_IRQ_HANDLER_HIGHEST_ORDER_PRIORITY-1)

