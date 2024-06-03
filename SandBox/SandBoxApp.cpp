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
        std::string shaderPath = m_RootPath+"/SandBox/assets/shaders/testShader.glsl";
        m_Shader.reset(Shader::Create(shaderPath.c_str()));
        m_Shader->Bind();
        m_Shader->SetInt("testTexture",0);

        std::string texPath = m_RootPath+"/SandBox/assets/textures/awesomeface.png";
        m_Texture = Texture2D::Create(texPath.c_str());

        m_CameraController = new OrthographicCameraController(1200.0f / 800.0f);

        m_PerspectiveCamera = new PerspectiveCamera(glm::vec3(0.0f,0.0f,3.0f));
    }

    void OnUpdate(Timestep ts) override{
        m_CameraController->OnUpdate(ts);
        RenderCommand::SetClearColor({0.45f, 0.55f, 0.60f, 1.00f});
        RenderCommand::Clear();

        // 1、正交相机
        Renderer::BeginScene(m_CameraController->GetCamera().GetViewProjectionMatrix());

        // 2、透视相机，目前固定位置，后续可以增加对应controller实现事件监视等
        // // pass projection matrix to shader (note that in this case it could change every frame)
        // glm::mat4 projection = glm::perspective(glm::radians(m_PerspectiveCamera->Zoom), (float)1200 / (float)800, 0.1f, 100.0f);
        // // camera/view transformation
        // glm::mat4 view = m_PerspectiveCamera->GetViewMatrix();
        // Renderer::BeginScene(projection*view);
    
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
    OrthographicCameraController *m_CameraController;
    std::shared_ptr<Texture2D> m_Texture;

    PerspectiveCamera *m_PerspectiveCamera;
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