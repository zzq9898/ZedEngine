#include "Texture.h"
#include "Zed/Renderer/Renderer.h"
#include "Zed/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Zed {

    std::shared_ptr<Texture2D> Texture2D::Create(const std::string &path) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None: ZED_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
        }

        ZED_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }
}