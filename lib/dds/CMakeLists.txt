project(dds)

add_library(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC comlib hardware_dma hardware_spi cmsis)
target_sources(${PROJECT_NAME}
    PRIVATE
        dds.c
        dds.h
        dac.c
        dac.h
)