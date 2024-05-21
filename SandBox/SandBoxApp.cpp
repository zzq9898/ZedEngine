#include <ZedEntry.h>

using  namespace Zed;

class ExampleLayer : public Zed::Layer {
public:
    ExampleLayer() : Layer("Example") {
        testInitRendering();
    }

    void OnUpdate() override{
        RenderCommand::SetClearColor({0.45f, 0.55f, 0.60f, 1.00f});
        RenderCommand::Clear();
        Renderer::BeginScene(*m_Camera);
        m_Camera->SetPosition({0.5f, 0.5f, 0.0f});
        m_Camera->SetRotation(45.0f);
        Renderer::Submit(m_Shader,m_VertexArray);
        Renderer::EndScene();
    }

    void OnEvent(Zed::Event& event) override {

    }

private:
    // Test:用于渲染
    std::shared_ptr<VertexBuffer> m_VertexBuffer;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<VertexArray> m_VertexArray;
    OrthographicCamera *m_Camera;

    void testInitRendering() {
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
                                         uniform mat4 u_ViewProjection;
                                         out vec3 color;
                                         void main()
                                         {
                                            gl_Position = u_ViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
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

        m_Camera = new OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f);
    }
};

class Sandbox : public Zed::Application {
public:
    Sandbox(){
        PushLayer(new ExampleLayer());
    }

    ~Sandbox()
    {

    }
};

Zed::Application* Zed::CreateApplication() {
    return new Sandbox();
}