cmake_minimum_required(VERSION 3.1)
project(Construct3)

set(CMAKE_SKIP_INSTALL_RULES TRUE)
set(C3_BINARY_DIR ${CMAKE_BINARY_DIR}/Binary)

#Place external projects here
add_subdirectory(Thirdparty)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${C3_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${C3_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${C3_BINARY_DIR})
if(UNIX)
    set(BUILD_SHARED_LIBS ON)
else()
    set(BUILD_SHARED_LIBS OFF)
endif()
add_subdirectory(Core)
add_subdirectory(Editor) # -> Core, Engine, OpenGL3Render
add_subdirectory(Engine) # -> Core
add_subdirectory(OpenGL3Render) # -> Core
add_subdirectory(Launcher) # -> Core, OpenGL3Render
