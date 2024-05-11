#ifndef ZED_APPLICATION_H
#define ZED_APPLICATION_H

#include <memory>
#include "Zed/Core/Window.h"
#include "Zed/Core/LayerStack.h"
#include "Zed/Events/Event.h"
#include "Zed/Events/ApplicationEvent.h"
#include "Zed/ImGui/ImGuiLayer.h"
namespace Zed{
    class Application {
    public:
        Application();
        virtual ~Application();
        void Run();
        void OnEvent(Event& e);
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
        inline Window& GetWindow() {
            return *m_Window;
        }
        inline static Application& Get() {
            return *s_Instance;
        }
    private:
        bool OnWindowClose(WindowCloseEvent& e);

        static Application* s_Instance;
        std::unique_ptr<Window> m_Window;
        bool m_isRunning = true;
        LayerStack m_LayerStack;
        ImGuiLayer* m_ImGuiLayer;

        // Test:用于渲染
        void testInitRendering();
        unsigned int m_VertexArray;
        unsigned int m_VertexBuffer, m_IndexBuffer;
        unsigned int shaderProgram;
    };

    Application* CreateApplication();
}



#endif //ZED_APPLICATION_H