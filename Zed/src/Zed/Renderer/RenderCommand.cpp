#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Zed{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}