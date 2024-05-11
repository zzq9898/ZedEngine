cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)
project(ZedEngine)

file (GLOB SRC_LIST_IMGUI
        vendor/imgui/*.h
        vendor/imgui/*.cpp
)

set(SRC_LIST_IMGUI_BACKENDS
        vendor/imgui/backends/imgui_impl_opengl3.h
        vendor/imgui/backends/imgui_impl_opengl3.cpp
        vendor/imgui/backends/imgui_impl_opengl3_loader.h
        vendor/imgui/backends/imgui_impl_glfw.h
        vendor/imgui/backends/imgui_impl_glfw.cpp
)

file(GLOB SRC_LIST 
    vendor/GLAD/src/glad.c
    src/Platform/Windows/WindowsWindow.cpp
    src/Platform/Windows/WindowsInput.cpp
    src/Platform/OpenGL/*.cpp
    src/Zed/Core/Application.cpp
    src/Zed/Core/Log.cpp
    src/Zed/Core/Layer.cpp
    src/Zed/Core/LayerStack.cpp
    src/Zed/ImGui/ImGuiLayer.cpp
    src/Zed/Renderer/*.cpp)

add_library(ZedEngine STATIC ${SRC_LIST} ${SRC_LIST_IMGUI} ${SRC_LIST_IMGUI_BACKENDS})

# 编译子项目 GLFW
add_subdirectory(vendor/GLFW)
target_link_libraries(ZedEngine  glfw)

target_include_directories(ZedEngine PUBLIC 
                            vendor/spdlog/include
                            vendor/GLAD/include
                            vendor/GLFW/include
                            vendor/imgui
                            vendor/imgui/backends
                            vendor/glm
                            src)

target_compile_definitions(ZedEngine PUBLIC
                                ZED_ENABLE_ASSERTS)