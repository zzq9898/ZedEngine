#ifndef ZED_APPLICATION_H
#define ZED_APPLICATION_H

#include <memory>
#include "Zed/Core/Window.h"
#include "Zed/Core/LayerStack.h"
#include "Zed/Events/Event.h"
#include "Zed/Events/ApplicationEvent.h"
namespace Zed{
    class Application {
    public:
        Application();
        virtual ~Application();
        void Run();
        void OnEvent(Event& e);
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
    private:
        bool OnWindowClose(WindowCloseEvent& e);
        std::unique_ptr<Window> m_window;
        bool is_running = true;
        LayerStack m_LayerStack;
    };

    Application* CreateApplication();
}



#endif //ZED_APPLICATION_H