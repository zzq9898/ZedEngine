#pragma once

#include <glm/glm.hpp>
#include "Zed/Renderer/RendererAPI.h"
#include "Zed/Renderer/VertexArray.h"

namespace Zed {
    class RenderCommand {
    public:
        static inline void Init() {
            s_RendererAPI->Init();
        }
        static inline void SetClearColor(const glm::vec4& color) {
            s_RendererAPI->SetClearColor(color);
        }
        static inline void Clear() {
            s_RendererAPI->Clear();
        }
        static inline void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
            s_RendererAPI->DrawIndexed(vertexArray);
        }
    private:
        static RendererAPI* s_RendererAPI;
    };
}