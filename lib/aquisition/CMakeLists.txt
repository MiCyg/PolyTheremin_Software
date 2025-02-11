project(aquisition)

add_library(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC comlib hardware_pwm cmsis freq_meas)
target_sources(${PROJECT_NAME}
	PRIVATE 
        aquisition.c
)