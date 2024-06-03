#pragma once
#include "Zed/Renderer/RendererAPI.h"
#include "Zed/Renderer/Shader.h"
#include "Zed/Camera/OrthographicCamera.h"
namespace Zed {
    class Renderer {
    public:
        static void Init();
        static void BeginScene(OrthographicCamera &camera);
        static void EndScene();
        static void Submit(const std::shared_ptr<Shader> &shader, 
                    const std::shared_ptr<VertexArray> &vertexArray, 
                    const glm::mat4 &modelMatrix);

        inline static RendererAPI::API GetAPI() {
            return RendererAPI::GetAPI();
        }
        struct SceneData {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData* m_SceneData;
    };
}