#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "Zed/Renderer/VertexArray.h"

namespace Zed {
    class RendererAPI {
    public:
        enum class API {
            None = 0, OpenGL = 1 // 扩展API
        };

        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;
        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
        inline static API GetAPI() {return s_API;}

    private:
        static API s_API;
    };
}