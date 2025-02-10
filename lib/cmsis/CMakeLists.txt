
cmake_minimum_required(VERSION 3.13)

project(cmsis)

add_library(${PROJECT_NAME})


# For cmsis library
set(CMSISCORE CMSIS_6/CMSIS/Core)
# set(CMSISCORE ${CMAKE_SOURCE_DIR}/lib/CMSIS_6/CMSIS/Core)
set(CMSISDSP ${CMAKE_SOURCE_DIR}/lib/cmsis/CMSIS-DSP)

target_link_libraries(${PROJECT_NAME} 
	PUBLIC 
		comlib 	
)

target_include_directories(${PROJECT_NAME} 
	PUBLIC 
		${PROJECT_SOURCE_DIR}
		${CMSISDSP}/Include
		${CMSISDSP}/Include/dsp
		${CMSISCORE}/Include
	)

target_sources(${PROJECT_NAME}
	PUBLIC
	cmsis.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_abs_f16.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_add_f16.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_add_f32.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_add_f64.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_add_q15.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_add_q31.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_add_q7.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_dot_prod_f16.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_dot_prod_f32.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_dot_prod_f64.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_dot_prod_q15.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_dot_prod_q31.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_dot_prod_q7.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_mult_f16.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_mult_f32.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_mult_f64.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_mult_q15.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_mult_q31.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_mult_q7.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_negate_f16.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_negate_f32.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_negate_f64.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_negate_q15.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_negate_q31.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_negate_q7.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_offset_f16.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_offset_f32.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_offset_f64.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_offset_q15.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_offset_q31.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_offset_q7.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_scale_f16.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_scale_f32.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_scale_f64.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_scale_q15.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_scale_q31.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_scale_q7.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_shift_q15.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_shift_q31.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_shift_q7.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_sub_f16.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_sub_f32.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_sub_f64.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_sub_q15.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_sub_q31.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_sub_q7.c
	
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmax_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmax_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmax_q15.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmax_q31.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmax_q7.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmin_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmin_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmin_q15.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmin_q31.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmin_q7.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_max_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_max_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_max_q15.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_max_q31.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_max_q7.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_mean_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_mean_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_mean_q15.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_mean_q31.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_mean_q7.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_min_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_min_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_min_q15.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_min_q31.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_min_q7.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_power_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_power_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_power_q15.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_power_q31.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_power_q7.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_rms_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_rms_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_rms_q15.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_rms_q31.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_std_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_std_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_std_q15.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_std_q31.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_var_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_var_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_var_q15.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_var_q31.c

)

# add_subdirectory(CMSIS-DSP/Source bin_dsp)
