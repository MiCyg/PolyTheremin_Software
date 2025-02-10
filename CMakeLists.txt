# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

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
pico_sdk_init()

project(PolyTheremin_Software
    VERSION 1.0.0
    DESCRIPTION "Polyphonic Theremin Software for RP2040"
    # TODO HOMEPAGE_URL "https://my.happy.polytheremin.page"
    LANGUAGES C CXX ASM
)

# Release configuration
set(PROJECT_NAME ${CMAKE_PROJECT_NAME})
set(VERSION_NUMBER "1.0.0")
set(VERSION_DESCRIPITION "")

set(MAIN_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}")
set(FREERTOS_SRC_DIRECTORY "${CMAKE_SOURCE_DIR}/freertos/FreeRTOS-Kernel")
set(FREERTOS_CFG_DIRECTORY "${CMAKE_SOURCE_DIR}/freertos")


set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)







include(${FREERTOS_SRC_DIRECTORY}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

# Initialize Pico SDK

# Add subdirectories for libraries
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/)

# Create executable
add_executable(${PROJECT_NAME} 
    main.c
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
    comlib
    core
    pico_stdlib
    FreeRTOS-Kernel
    FreeRTOS-Kernel-Heap4
)

# Pico specific configurations
# pico_set_program_name(${PROJECT_NAME} "PolyTheremin")
# pico_set_program_version(${PROJECT_NAME} ${VERSION_NUMBER})

# Enable UART
pico_enable_stdio_uart(${PROJECT_NAME} 1)
# pico_enable_stdio_usb(${PROJECT_NAME} 1)

# Generate .uf2 file can be disabled on debug process
# pico_add_extra_outputs(${PROJECT_NAME})

