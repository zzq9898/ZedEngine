cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 11)
project(ZedEngine)

set(SRC_LIST 
    vendor/GLAD/src/glad.c
    src/Platform/Windows/WindowsWindow.cpp
    src/Zed/Core/Application.cpp
    src/Zed/Core/Log.cpp)

add_library(ZedEngine STATIC ${SRC_LIST})

# 编译子项目 GLFW
add_subdirectory(vendor/GLFW)
target_link_libraries(ZedEngine  glfw)

target_include_directories(ZedEngine PUBLIC 
                            vendor/spdlog/include
                            vendor/GLAD/include
                            vendor/GLFW/include
                            src)