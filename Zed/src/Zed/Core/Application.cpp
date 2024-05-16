#include <iostream>
#include <functional>
#include "Zed/Core/Application.h"
#include "Zed/Core/Log.h"
#include "Zed/Events/ApplicationEvent.h"

namespace Zed{
    #define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
    Application* Application::s_Instance = nullptr;

    Application::Application() {
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        testInitRendering();
    }

    Application::~Application() {

    }

    void Application::testInitRendering(){
        m_VertexArray.reset(VertexArray::Create());

        float vertices[6 * 3] = {
                // pos             //color
                -0.5f, -0.5, 0.0,  1.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.5f, 0.0f,  0.0f, 0.0f, 1.0f
        };
        m_VertexBuffer.reset(VertexBuffer::Create(vertices,sizeof(vertices)));
        
        // 设置layout
        BufferLayout layout = {
                {ShaderDataType::Float3, "aPos"},
                {ShaderDataType::Float3, "aColor"},
        };
        m_VertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        
        unsigned int indices[3] = {0, 1, 2};
        m_IndexBuffer.reset(IndexBuffer::Create(indices,sizeof(indices)/sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);
        // build and compile our shader program
        // ------------------------------------
        // vertex shader

        const char *vertexShaderSource = R"(#version 330 core
                                         layout (location = 0) in vec3 aPos;
                                         layout (location = 1) in vec3 aColor;
                                         out vec3 color;
                                         void main()
                                         {
                                            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
                                            color = aColor;
                                         })";
        const char *fragmentShaderSource = R"(#version 330 core
                                           out vec4 FragColor;
                                           in vec3 color;
                                           void main()
                                           {
                                             FragColor = vec4(color, 1.0f);
                                           })";
        m_Shader = std::make_unique<Shader>(vertexShaderSource,fragmentShaderSource);
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
            glClearColor(0.1, 0.1, 0.1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();
            m_VertexArray->Bind();
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

            for (Layer* layer : m_LayerStack) {
                layer->OnUpdate();
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