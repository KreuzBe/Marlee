cmake_minimum_required(VERSION 3.16)
project(Marlee)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(dependencies/glfw)

find_package(OpenGL REQUIRED)

add_executable(Marlee main.cpp)
target_link_libraries(Marlee glfw)