project (lidar_viz)

find_package(OpenGL REQUIRED)

aux_source_directory(. SOURCE_FILES)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
    ${OPENGL_LIBRARY}
    glfw
    GLEW
)

