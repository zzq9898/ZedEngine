#include "Shader.h"
#include "Zed/Core/Log.h"
#include "Zed/Core/Base.h"
#include "Zed/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
namespace Zed {
    Shader *Shader::Create(const std::string& filePath) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:
                ZED_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return new OpenGLShader(filePath);

        }
        ZED_CORE_ASSERT(false, "Shader::Create() null return!");
        return nullptr;
    }

    Shader *Shader::Create(const std::string &vertexSrc, const std::string &fragmentSrc) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:
                ZED_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
                return nullptr;
            case RendererAPI::API::OpenGL:
                return new OpenGLShader(vertexSrc, fragmentSrc);
        }
        ZED_CORE_ASSERT(false, "Shader::Create() null return!");
        return nullptr;
    }
}