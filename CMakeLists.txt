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
        Source/Render.cpp
        Source/stb_image.cpp
        Source/Camera.cpp
        Source/Input.cpp
        Source/MeshLoader.cpp
        Source/Mesh.cpp
        Source/Model.cpp
        Source/VertexData.cpp

        Headers/cube.h
        Headers/stb_image.h
        Headers/Window.h
        Headers/Texture.h
        Headers/Shader.h
        Headers/Render.h
        Headers/Camera.h
        Headers/Input.h
        Headers/KeyCode.h
        Headers/MeshLoader.h
        Headers/Mesh.h
        Headers/Model.h
        Headers/VertexData.h)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(ExternalDependencies/glfw)
add_subdirectory(ExternalDependencies/glm)

target_link_libraries(RefraEngine glfw)
target_link_libraries(RefraEngine glm)