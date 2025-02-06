project(freq_meas)

add_library(${PROJECT_NAME} STATIC freq_meas.c)
set_source_files_properties(freq_meas.c PROPERTIES COMPILE_FLAGS -fno-common)
target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC comlib)
target_link_libraries(${PROJECT_NAME} 
	PUBLIC 
	hardware_dma 
	hardware_pwm
)
