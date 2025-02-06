
cmake_minimum_required(VERSION 3.13)

project(cmsis)

add_library(${PROJECT_NAME})


# For cmsis library
set(CMSISCORE CMSIS_6/CMSIS/Core)
# set(CMSISCORE ${CMAKE_SOURCE_DIR}/lib/CMSIS_6/CMSIS/Core)
# set(CMSISDSP ${CMAKE_SOURCE_DIR}/lib/cmsis/CMSIS-DSP)


target_include_directories(${PROJECT_NAME} 
	PUBLIC 
		${PROJECT_SOURCE_DIR}
		# ${CMSISCORE}/Include
		# ${CMSISCORE}/Include/m-profile
	)

target_link_libraries(${PROJECT_NAME} 
	PUBLIC 
		comlib 	
)

target_sources(${PROJECT_NAME}
	PUBLIC
	cmsis.c
	# ${CMSISCORE}/Source/irq_ctrl_gic.c

)

add_subdirectory(CMSIS-DSP/Source bin_dsp)
