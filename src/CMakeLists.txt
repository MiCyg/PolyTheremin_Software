
# Include app source code file(s)
add_executable(${PROJECT_NAME}
    ${APP_SRC_DIRECTORY}/main.c
)

# Link to built libraries
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC
    # FreeRTOS
	)
