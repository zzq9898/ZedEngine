#include "Zed/ImGui/ImGuiLayer.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "Zed/Core/Application.h"
#include "Zed/Core/Log.h"
namespace Zed {
    ImGuiLayer::~ImGuiLayer() {

    }

    void ImGuiLayer::OnAttach() {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImGui_ImplOpenGL3_Init("#version 330");
        Application& app = Application::Get();
        ImGui_ImplGlfw_InitForOpenGL(app.GetWindow().GetNativeWindow(), true);
    }

    void ImGuiLayer::OnDetach() {
    }

    void ImGuiLayer::Begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End() {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void ImGuiLayer::OnImGuiRender() {
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
    }
    
    // void ImGuiLayer::OnUpdate() {
    //     ImGuiIO& io = ImGui::GetIO();
    //     Application& app = Application::Get();
    //     io.DisplaySize = ImVec2( app.GetWindow().GetWidth(), 2  * app.GetWindow().GetHeight());

    //     float time = glfwGetTime();
    //     io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
    //     m_Time = time;

    //     ImGui_ImplOpenGL3_NewFrame();
    //     ImGui_ImplGlfw_NewFrame();
    //     ImGui::NewFrame();

    //     static bool show = true;
    //     ImGui::ShowDemoWindow(&show);

    //     ImGui::Render();

    //     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    // }

    // void ImGuiLayer::OnEvent(Zed::Event &event) {
    //     Layer::OnEvent(event);
    // }

    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer"){}
}