project(core)

add_library(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC 
	comlib 
	led_anim 
	het_generator
	aquisition
	dds
	button
)
target_sources(${PROJECT_NAME}
    PRIVATE
        core.c
)