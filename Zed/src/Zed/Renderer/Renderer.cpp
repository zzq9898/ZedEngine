#include "Renderer.h"
#include "Zed/Renderer/RenderCommand.h"

namespace Zed{
    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

    void Renderer::Init(){
        RenderCommand::Init();
    }

    void Renderer::BeginScene(const glm::mat4& ViewProjectionMatrix) {
        m_SceneData->ViewProjectionMatrix = ViewProjectionMatrix;
    }

    void Renderer::EndScene() {

    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader,
            const std::shared_ptr<VertexArray> &vertexArray,
            const glm::mat4& modelMatrix) {
        shader->Bind();
        shader->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
        shader->SetMat4("u_Model", modelMatrix);
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}