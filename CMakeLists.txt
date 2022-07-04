cmake_minimum_required(VERSION 3.22)
project(RefraEngine)

set(CMAKE_CXX_STANDARD 17)

include_directories(ExternalDependencies/include)
include_directories(Headers)

add_executable(RefraEngine
        Source/RefraEngine.cpp
        Source/glad.c
        Source/Window.cpp
        Source/Shader.cpp
        Source/Texture.cpp
        Source/Renderer.cpp
        Source/stb_image.cpp

        Headers/cube.h
        Headers/stb_image.h
        Headers/Window.h
        Headers/Texture.h
        Headers/Shader.h
        Headers/Renderer.h)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(ExternalDependencies/glfw)
add_subdirectory(ExternalDependencies/glm)

target_link_libraries(RefraEngine glfw)
target_link_libraries(RefraEngine glm)