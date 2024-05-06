cmake_minimum_required(VERSION 3.15)
project(Zed)
set(SRC_LIST src/Zed/Application.cpp)
add_library(ZedEngine STATIC ${SRC_LIST})