# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

# Release configuration
set(PROJECT_NAME PolyTheremin_Software)
set(VERSION_NUMBER "1.0.0")
set(VERSION_DESCRIPITION "")

set(MAIN_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}")
set(FREERTOS_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}/freertos/FreeRTOS-Kernel")
set(FREERTOS_CFG_DIRECTORY "${CMAKE_SOURCE_DIR}/freertos")


set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)
include(${FREERTOS_SRC_DIRECTORY}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

project(PolyTheremin_Software
		LANGUAGES C CXX ASM
)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()


add_subdirectory(${CMAKE_SOURCE_DIR}/lib)

add_executable(${PROJECT_NAME} main.c)


target_link_libraries(${PROJECT_NAME} 
	comlib
    )


pico_set_program_name(${PROJECT_NAME} nulnulnu)
pico_set_program_version(${PROJECT_NAME} ${VERSION_NUMBER})

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(${PROJECT_NAME} 1)
# pico_enable_stdio_usb(${PROJECT_NAME} 1)

pico_add_extra_outputs(${PROJECT_NAME})
