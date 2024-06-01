#include <ZedEntry.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

using namespace Zed;

class ExampleLayer : public Zed::Layer {
public:
    ExampleLayer() : Layer("Example") {
        m_RootPath = PROJECT_PATH;
    
        m_VertexArray.reset(VertexArray::Create());

        float vertices[8 * 4] = {
            // pos            //tex      //normal
            -1.0f, -1.0, 0.0, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, -1.0, 0.0, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
        };

        m_VertexBuffer.reset(VertexBuffer::Create(vertices,sizeof(vertices)));
        
        // 设置layout
        BufferLayout layout = {
                {ShaderDataType::Float3, "aPos"},
                {ShaderDataType::Float2, "aTexture"},
                {ShaderDataType::Float3, "aNormal"},
        };
        m_VertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        unsigned int indices[6] = {
            0, 1, 2,
            1, 3, 2
        };
        m_IndexBuffer.reset(IndexBuffer::Create(indices,sizeof(indices)/sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);
        // build and compile our shader program
        // ------------------------------------
        // vertex shader

        const char *vertexShaderSource = R"(#version 330 core
                                         layout (location = 0) in vec3 aPos;
                                         layout (location = 1) in vec2 aTexture;
                                         layout (location = 2) in vec3 aNormal;
                                         uniform mat4 u_ViewProjection;
                                         uniform mat4 u_Model;
                                         out vec2 TexCoord;
                                         out vec3 Normal;
                                         void main()
                                         {
                                            gl_Position = u_ViewProjection * u_Model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
                                            TexCoord = aTexture;
                                            Normal = aNormal;
                                         })";
        const char *fragmentShaderSource = R"(#version 330 core
                                           out vec4 FragColor;
                                           in vec2 TexCoord;
                                           in vec3 Normal;
                                           uniform sampler2D testTexture;
                                           void main()
                                           {
                                                vec4 color = texture(testTexture,TexCoord);
                                                FragColor = vec4(color);
                                           })";
        m_Shader = std::make_unique<Shader>(vertexShaderSource,fragmentShaderSource);
        m_Shader->Bind();
        m_Shader->SetInt("testTexture",0);

        std::string texPath = m_RootPath+"/SandBox/assets/textures/awesomeface.png";
        m_Texture = Texture2D::Create(texPath.c_str());

        m_Camera = new OrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f);

    }

    void OnUpdate() override{
        // 预留timestep
        float ts = 0.01;
        if (Zed::Input::IsKeyPressed(ZED_KEY_LEFT))
            m_CameraPosition.x -= m_CameraMoveSpeed * ts;
        else if (Zed::Input::IsKeyPressed(ZED_KEY_RIGHT))
            m_CameraPosition.x += m_CameraMoveSpeed * ts ;

        if (Zed::Input::IsKeyPressed(ZED_KEY_UP))
            m_CameraPosition.y += m_CameraMoveSpeed * ts ;
        else if (Zed::Input::IsKeyPressed(ZED_KEY_DOWN))
            m_CameraPosition.y -= m_CameraMoveSpeed * ts ;

        if (Zed::Input::IsKeyPressed(ZED_KEY_A))
            m_CameraRotation += m_CameraRotationSpeed * ts;
        if (Zed::Input::IsKeyPressed(ZED_KEY_D))
            m_CameraRotation -= m_CameraRotationSpeed * ts;

        RenderCommand::SetClearColor({0.45f, 0.55f, 0.60f, 1.00f});
        RenderCommand::Clear();
        Renderer::BeginScene(*m_Camera);
        m_Camera->SetPosition(m_CameraPosition);
        m_Camera->SetRotation(m_CameraRotation);

        glm::mat4 modelMat = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
        m_Texture->Bind(0);
        Renderer::Submit(m_Shader,m_VertexArray,modelMat);
        Renderer::EndScene();
    }

    void OnEvent(Zed::Event& event) override {

    }

private:
    std::string m_RootPath;
    // Test:用于渲染
    std::shared_ptr<VertexBuffer> m_VertexBuffer;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<VertexArray> m_VertexArray;
    glm::vec3 m_CameraPosition = glm::vec3(0.0);
    float m_CameraRotation = 0.0f;
    float m_CameraMoveSpeed = 5.f;
    float m_CameraRotationSpeed = 180.0f;
    OrthographicCamera *m_Camera;
    std::shared_ptr<Texture2D> m_Texture;
};

class Sandbox : public Zed::Application {
public:
    Sandbox(){
    #ifdef PROJECT_PATH
        ZED_INFO("Project Root Path : {0}", PROJECT_PATH);
    #else
        ZED_ERROR("No define Project Root Path!");
        exit(0);
    #endif

        PushLayer(new ExampleLayer());
    }

    ~Sandbox()
    {

    }
};

Zed::Application* Zed::CreateApplication() {
    return new Sandbox();
}