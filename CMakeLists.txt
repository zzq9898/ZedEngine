cmake_minimum_required(VERSION 3.15)

project(SandBox)
set(SRC_LIST SandBox/SandBoxApp.cpp)

add_subdirectory(Zed)

add_definitions(-DPROJECT_PATH="${PROJECT_SOURCE_DIR}")

add_executable(mySandBox ${SRC_LIST})

target_link_libraries(mySandBox ZedEngine)
target_include_directories(mySandBox PRIVATE Zed/src)