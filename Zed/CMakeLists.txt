cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 11)
project(ZedEngine)

set(SRC_LIST 
    src/Zed/Core/Application.cpp
    src/Zed/Core/Log.cpp)

add_library(ZedEngine STATIC ${SRC_LIST})

target_include_directories(ZedEngine PUBLIC 
                            vendor/spdlog/include
                            src)