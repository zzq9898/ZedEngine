#include <functional>
#include "Zed/Core/Application.h"
#include "Zed/Core/Log.h"
#include "Zed/Events/ApplicationEvent.h"
#include <glad/glad.h>

namespace Zed{
    #define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
    Application::Application() {
        m_window = std::unique_ptr<Window>(Window::Create());
        m_window->SetEventCallback(BIND_EVENT_FN(OnEvent));
    }

    Application::~Application() {

    }

    void Application::PushLayer(Layer *layer) {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer *layer) {
        m_LayerStack.PushOverlay(layer);
    }

    void Application::OnEvent(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        ZED_CORE_TRACE("{0}", e.ToString());

        for (auto it = m_LayerStack.end();  it != m_LayerStack.begin();) {
            (*--it)->OnEvent(e);
            if (e.Handled) {
                break;
            }
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent &e) {
        is_running = false;
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

        while(is_running) {
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate();
            }
            m_window->OnUpdate();
        }
    }

}