project(het_generator)

add_library(${PROJECT_NAME} STATIC het_generator.c)
pico_generate_pio_header(het_generator ${CMAKE_CURRENT_LIST_DIR}/het_generator.pio)
set_source_files_properties(het_generator.c PROPERTIES COMPILE_FLAGS -fno-common)
target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC comlib)
target_link_libraries(${PROJECT_NAME} 
	PUBLIC 
	hardware_pio
)


# add_executable(het_generator)

# pico_add_extra_outputs(het_generator)
# # add url via pico_set_program_url

