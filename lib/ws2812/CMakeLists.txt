project(ws2812)

add_library(${PROJECT_NAME} STATIC ws2812.c)
pico_generate_pio_header(ws2812 ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)
set_source_files_properties(ws2812.c PROPERTIES COMPILE_FLAGS -fno-common)
target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC comlib)
target_link_libraries(${PROJECT_NAME} 
	PUBLIC 
	hardware_pio
)

