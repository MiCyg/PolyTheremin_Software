# project(comlib)

# add_library(${PROJECT_NAME})

# target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR} ${FREERTOS_CFG_DIRECTORY})

# target_link_libraries(${PROJECT_NAME} PUBLIC pico_stdlib hardware_gpio FreeRTOS-Kernel-Heap4 FreeRTOS-Kernel)
# target_sources(${PROJECT_NAME}
#     PRIVATE
#         comlib.h
# )

cmake_minimum_required(VERSION 3.13)

# Project name
project(comlib)

# Create library target
add_library(${PROJECT_NAME})

# Add source files
target_sources(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/comlib.h
)

# Include directories
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/
		${FREERTOS_CFG_DIRECTORY}
)

# Link dependencies
target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
        pico_stdlib 
        hardware_gpio 
        FreeRTOS-Kernel-Heap4 
        FreeRTOS-Kernel
)

