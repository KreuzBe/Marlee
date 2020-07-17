cmake_minimum_required(VERSION 3.16)
project(Marlee)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(dependencies/glfw)
find_package(OpenGL REQUIRED)



find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message("ERROR: OpenGL not found")
endif(NOT OPENGL_FOUND)
set(GL_LIBRARY GL GLU X11)

add_executable(Marlee main.cpp)
target_link_libraries(Marlee OpenGL::GL)
target_link_libraries(Marlee glfw GLEW libGLEW.so libGLU.so libGL.so)
