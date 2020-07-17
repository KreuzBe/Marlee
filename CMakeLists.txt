cmake_minimum_required(VERSION 3.16)
project(Marlee)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory(dependencies/glfw)
find_package(OpenGL REQUIRED)

#GLEW
include(ExternalProject)
ExternalProject_Add(glew_download
        URL https://netix.dl.sourceforge.net/project/glew/glew/2.1.0/glew-2.1.0-win32.zip
        BUILD_COMMAND ""
        CONFIGURE_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND ""
        )
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/glew_download-prefix/src/glew_download/include)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/glew_download-prefix/src/glew_download/lib/Release/x64/)
add_library(GLEW STATIC IMPORTED DEPENDS glew_download)
set_target_properties(GLEW PROPERTIES
        IMPORTED_LOCATION "${PROJECT_BINARY_DIR}/glew_download-prefix/src/glew_download/lib/Release/x64/glew32s.lib"
        INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_BINARY_DIR}/glew_download-prefix/src/glew_download/include/")


add_executable(Marlee main.cpp)
add_dependencies(Marlee GLEW glew_download)
target_link_libraries(Marlee glfw GLEW OpenGL::GL)

