
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
target_compile_options(${PROJECT_NAME} PUBLIC 
    -Wsign-compare
    -Wdouble-promotion
    -Ofast -ffast-math
    -DNDEBUG
    -Wall -Wextra  
	# -Werror
    -fshort-enums 
    # -fshort-wchar
)

target_sources(${PROJECT_NAME}
	PUBLIC
	cmsis.c

	# ${CMSISDSP}/Source/BasicMathFunctions/BasicMathFunctions.c
	# ${CMSISDSP}/Source/BasicMathFunctions/BasicMathFunctionsF16.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_abs_f16.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_abs_f32.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_abs_f64.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_abs_q15.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_abs_q31.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_abs_q7.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_add_f16.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_add_f32.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_add_f64.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_add_q15.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_add_q31.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_add_q7.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_and_u16.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_and_u32.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_and_u8.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_clip_f16.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_clip_f32.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_clip_q15.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_clip_q31.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_clip_q7.c
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
	${CMSISDSP}/Source/BasicMathFunctions/arm_not_u16.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_not_u32.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_not_u8.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_offset_f16.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_offset_f32.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_offset_f64.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_offset_q15.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_offset_q31.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_offset_q7.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_or_u16.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_or_u32.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_or_u8.c
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
	${CMSISDSP}/Source/BasicMathFunctions/arm_xor_u16.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_xor_u32.c
	${CMSISDSP}/Source/BasicMathFunctions/arm_xor_u8.c

	# ${CMSISDSP}/Source/StatisticsFunctions/StatisticsFunctions.c
	# ${CMSISDSP}/Source/StatisticsFunctions/StatisticsFunctionsF16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmax_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmax_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmax_f64.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmax_no_idx_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmax_no_idx_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmax_no_idx_f64.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmax_no_idx_q15.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmax_no_idx_q31.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmax_no_idx_q7.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmax_q15.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmax_q31.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmax_q7.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmin_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmin_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmin_f64.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmin_no_idx_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmin_no_idx_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmin_no_idx_f64.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmin_no_idx_q15.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmin_no_idx_q31.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmin_no_idx_q7.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmin_q15.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmin_q31.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_absmin_q7.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_accumulate_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_accumulate_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_accumulate_f64.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_entropy_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_entropy_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_entropy_f64.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_kullback_leibler_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_kullback_leibler_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_kullback_leibler_f64.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_logsumexp_dot_prod_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_logsumexp_dot_prod_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_logsumexp_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_logsumexp_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_max_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_max_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_max_f64.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_max_no_idx_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_max_no_idx_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_max_no_idx_f64.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_max_no_idx_q15.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_max_no_idx_q31.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_max_no_idx_q7.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_max_q15.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_max_q31.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_max_q7.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_mean_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_mean_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_mean_f64.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_mean_q15.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_mean_q31.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_mean_q7.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_min_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_min_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_min_f64.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_min_no_idx_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_min_no_idx_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_min_no_idx_f64.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_min_no_idx_q15.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_min_no_idx_q31.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_min_no_idx_q7.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_min_q15.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_min_q31.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_min_q7.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_mse_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_mse_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_mse_f64.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_mse_q15.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_mse_q31.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_mse_q7.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_power_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_power_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_power_f64.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_power_q15.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_power_q31.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_power_q7.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_rms_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_rms_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_rms_q15.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_rms_q31.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_std_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_std_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_std_f64.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_std_q15.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_std_q31.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_var_f16.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_var_f32.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_var_f64.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_var_q15.c
	${CMSISDSP}/Source/StatisticsFunctions/arm_var_q31.c




	# ${CMSISDSP}/Source/TransformFunctions/TransformFunctions.c
	# ${CMSISDSP}/Source/TransformFunctions/TransformFunctionsF16.c
	${CMSISDSP}/Source/TransformFunctions/arm_bitreversal.c
	${CMSISDSP}/Source/TransformFunctions/arm_bitreversal2.c
	${CMSISDSP}/Source/TransformFunctions/arm_bitreversal_f16.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_f16.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_f32.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_f64.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_init_f16.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_init_f32.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_init_f64.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_init_q15.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_init_q31.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_q15.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_q31.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_radix2_f16.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_radix2_f32.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_radix2_init_f16.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_radix2_init_f32.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_radix2_init_q15.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_radix2_init_q31.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_radix2_q15.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_radix2_q31.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_radix4_f16.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_radix4_f32.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_radix4_init_f16.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_radix4_init_f32.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_radix4_init_q15.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_radix4_init_q31.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_radix4_q15.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_radix4_q31.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_radix8_f16.c
	${CMSISDSP}/Source/TransformFunctions/arm_cfft_radix8_f32.c
	${CMSISDSP}/Source/TransformFunctions/arm_mfcc_f16.c
	${CMSISDSP}/Source/TransformFunctions/arm_mfcc_f32.c
	${CMSISDSP}/Source/TransformFunctions/arm_mfcc_init_f16.c
	${CMSISDSP}/Source/TransformFunctions/arm_mfcc_init_f32.c
	${CMSISDSP}/Source/TransformFunctions/arm_mfcc_init_q15.c
	${CMSISDSP}/Source/TransformFunctions/arm_mfcc_init_q31.c
	${CMSISDSP}/Source/TransformFunctions/arm_mfcc_q15.c
	${CMSISDSP}/Source/TransformFunctions/arm_mfcc_q31.c
	${CMSISDSP}/Source/TransformFunctions/arm_rfft_fast_f16.c
	${CMSISDSP}/Source/TransformFunctions/arm_rfft_fast_f32.c
	${CMSISDSP}/Source/TransformFunctions/arm_rfft_fast_f64.c
	${CMSISDSP}/Source/TransformFunctions/arm_rfft_fast_init_f16.c
	${CMSISDSP}/Source/TransformFunctions/arm_rfft_fast_init_f32.c
	${CMSISDSP}/Source/TransformFunctions/arm_rfft_fast_init_f64.c
	${CMSISDSP}/Source/TransformFunctions/arm_rfft_init_q15.c
	${CMSISDSP}/Source/TransformFunctions/arm_rfft_init_q31.c
	${CMSISDSP}/Source/TransformFunctions/arm_rfft_q15.c
	${CMSISDSP}/Source/TransformFunctions/arm_rfft_q31.c
		


	# ${CMSISDSP}/Source/CommonTables/CommonTables.c
	# ${CMSISDSP}/Source/CommonTables/CommonTablesF16.c
	${CMSISDSP}/Source/CommonTables/arm_common_tables.c
	${CMSISDSP}/Source/CommonTables/arm_common_tables_f16.c
	${CMSISDSP}/Source/CommonTables/arm_const_structs.c
	${CMSISDSP}/Source/CommonTables/arm_const_structs_f16.c
	${CMSISDSP}/Source/CommonTables/arm_mve_tables.c
	${CMSISDSP}/Source/CommonTables/arm_mve_tables_f16.c
	${CMSISDSP}/Source/CommonTables/arm_neon_tables.c
	${CMSISDSP}/Source/CommonTables/arm_neon_tables_f16.c
)

# add_subdirectory(CMSIS-DSP/Source bin_dsp)
