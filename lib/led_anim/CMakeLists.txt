project(led_anim)

add_library(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC comlib ws2812)
target_sources(${PROJECT_NAME}
    PRIVATE
        led_anim.h
        led_anim.c
)