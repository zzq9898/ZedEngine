#include <iostream>
#include <functional>
#include "Zed/Core/Application.h"
#include "Zed/Core/Log.h"
#include "Zed/Events/ApplicationEvent.h"
#include "Zed/Renderer/Renderer.h"

namespace Zed{
    Application* Application::s_Instance = nullptr;

    Application::Application() {
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(ZED_BIND_EVENT_FN(OnEvent));
        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        Renderer::Init();
    }

    Application::~Application() {

    }

    void Application::PushLayer(Layer *layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *layer) {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::OnEvent(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(ZED_BIND_EVENT_FN(OnWindowClose));
        ZED_CORE_TRACE("{0}", e.ToString());

        for (auto it = m_LayerStack.end();  it != m_LayerStack.begin();) {
            (*--it)->OnEvent(e);
            if (e.Handled) {
                break;
            }
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent &e) {
        m_isRunning = false;
        return true;
    }

    void Application::Run() {
        WindowResizeEvent e(1200, 720);
        if (e.IsInCategory(EventCategoryApplication)) {
            ZED_TRACE(e.ToString());
        }

        if (e.IsInCategory(EventCategoryInput)) {
            ZED_TRACE(e.ToString());
        }

        while(m_isRunning) {
            float time = glfwGetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate(timestep);
            }
            m_ImGuiLayer->Begin();
            for(Layer* layer : m_LayerStack) {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();
    
            m_Window->OnUpdate();
        }
    }

}