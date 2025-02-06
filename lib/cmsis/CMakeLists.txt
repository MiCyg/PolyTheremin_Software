


add_subdirectory(${CMSISDSP}/Source bin_dsp)

target_include_directories(${PROJECT_NAME} INTERFACE
	
		${CMSISCORE}/Include
		${CMSISDSP}/Include
)
target_link_libraries(${PROJECT_NAME} 
	INTERFACE 
		arm_cortexM4lf_math
)