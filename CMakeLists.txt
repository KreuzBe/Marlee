cmake_minimum_required(VERSION 3.16)
project(Marlee)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glew)
find_package(OpenGL REQUIRED)


add_executable(Marlee main.cpp)
target_link_libraries(Marlee OpenGL::GL)
target_link_libraries(Marlee glfw)
