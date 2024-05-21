#include "VertexArray.h"
#include "Zed/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Zed{
    VertexArray* VertexArray::Create() {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: ZED_CORE_ASSERT(false, "RendererAPI::None is currently not suported!"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
        }

        ZED_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }
}