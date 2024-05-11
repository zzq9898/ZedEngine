#include "OpenGLContext.h"
#include "Zed/Core/Base.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Zed {
    OpenGLContext::OpenGLContext(GLFWwindow *windowHandle):m_WindowHandle(windowHandle) {
        ZED_CORE_ASSERT(windowHandle, "Window handle is null");
    }

    void OpenGLContext::Init() {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        ZED_CORE_ASSERT(status, "Failed to initialize Glad!");

        ZED_CORE_INFO("OpenGL Info:");
        ZED_CORE_INFO(" Vendor: {0}", (char*)glGetString(GL_VENDOR));
        ZED_CORE_INFO(" Renderer: {0}", (char*)glGetString(GL_RENDERER));
        ZED_CORE_INFO(" Version: {0}", (char*)glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(m_WindowHandle);
    }
}