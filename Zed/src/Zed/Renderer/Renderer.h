#pragma once

namespace Zed {
    enum class RendererAPI {
        None = 0, OpenGL = 1//后续扩展其他API
    };

    class Renderer {
    public:
        inline static RendererAPI GetAPI() {
            return s_RendererAPI;
        }
    private:
        static RendererAPI s_RendererAPI;
    };
}