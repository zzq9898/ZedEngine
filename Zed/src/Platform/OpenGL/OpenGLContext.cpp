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
    }

    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(m_WindowHandle);
    }
}