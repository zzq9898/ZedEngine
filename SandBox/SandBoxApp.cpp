#include <ZedEntry.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

#include "CommonObjects.h"

using namespace Zed;

class ExampleLayer : public Zed::Layer {
public:
    ExampleLayer() : Layer("Example") {
        #ifdef PROJECT_PATH
            m_RootPath = PROJECT_PATH;
        #else
            ZED_ERROR("No define Project Root Path!");
            exit(0);
        #endif

        // 读取object
        std::vector<float> vertices;
        std::vector<unsigned int> indices;
        CommonObj::getSphereObj(vertices,indices);

        // vbo
        m_VertexBuffer.reset(VertexBuffer::Create(&vertices[0],sizeof(float)*vertices.size()));
        
        BufferLayout layout = {
                {ShaderDataType::Float3, "aPos"},
                {ShaderDataType::Float2, "aTexture"},
                {ShaderDataType::Float3, "aNormal"},
        };
        m_VertexBuffer->SetLayout(layout);

        // ebo
        m_IndexBuffer.reset(IndexBuffer::Create(&indices[0], indices.size()));

        // vao
        m_VertexArray.reset(VertexArray::Create());
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        // build and compile our shader program
        // ------------------------------------
        std::string shaderPath = m_RootPath+"/SandBox/assets/shaders/testShader.glsl";
        m_Shader.reset(Shader::Create(shaderPath.c_str()));
        m_Shader->Bind();
        m_Shader->SetInt("testTexture",0);

        std::string texPath = m_RootPath+"/SandBox/assets/textures/awesomeface.png";
        m_Texture = Texture2D::Create(texPath.c_str());

        m_CameraController = std::make_shared<PerspectiveCameraController>(glm::vec3(0.0, 0.0, 3.0));
    }

    void OnUpdate(Timestep ts) override{
        m_CameraController->OnUpdate(ts);
        RenderCommand::SetClearColor({0.45f, 0.55f, 0.60f, 1.00f});
        RenderCommand::Clear();

        // 透视相机设置PV矩阵
        Renderer::BeginScene(m_CameraController->GetProjectionMatrix() * m_CameraController->GetViewMatrix());

        glm::mat4 modelMat = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
        m_Texture->Bind(0);
        Renderer::Submit(m_Shader,m_VertexArray,modelMat);
        Renderer::EndScene();
    }

    void OnEvent(Zed::Event& event) override {
        m_CameraController->OnEvent(event);
    }

private:
    std::string m_RootPath;
    // Test:用于渲染
    std::shared_ptr<VertexBuffer> m_VertexBuffer;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<VertexArray> m_VertexArray;
    std::shared_ptr<PerspectiveCameraController> m_CameraController;
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