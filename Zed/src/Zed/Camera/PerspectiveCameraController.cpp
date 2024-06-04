#include "PerspectiveCameraController.h"
#include "Zed/Core/Input.h"
#include "Zed/Core/ZedKeyCodes.h"
#include "Zed/Core/Base.h"

namespace Zed {
    PerspectiveCameraController::PerspectiveCameraController(glm::vec3 cameraPosition) 
        : m_Camera(cameraPosition)
    {}

    void PerspectiveCameraController::OnUpdate(Timestep ts) {
        if (Zed::Input::IsKeyPressed(ZED_KEY_A))
            m_Camera.ProcessKeyboard(LEFT, ts);
        else if (Zed::Input::IsKeyPressed(ZED_KEY_D))
            m_Camera.ProcessKeyboard(RIGHT, ts);

        if (Zed::Input::IsKeyPressed(ZED_KEY_W))
            m_Camera.ProcessKeyboard(FORWARD, ts);
        else if (Zed::Input::IsKeyPressed(ZED_KEY_S))
            m_Camera.ProcessKeyboard(BACKWARD, ts);

        if (Zed::Input::IsKeyPressed(ZED_KEY_Q))
            m_Camera.ProcessKeyboard(UP, ts);
        else if (Zed::Input::IsKeyPressed(ZED_KEY_E))
            m_Camera.ProcessKeyboard(DOWN, ts);
    }

    void PerspectiveCameraController::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(ZED_BIND_EVENT_FN(PerspectiveCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(ZED_BIND_EVENT_FN(PerspectiveCameraController::OnWindowsResized));
        dispatcher.Dispatch<MouseMovedEvent>(ZED_BIND_EVENT_FN(PerspectiveCameraController::OnMouseMoved));
        dispatcher.Dispatch<MouseButtonPressedEvent>(ZED_BIND_EVENT_FN(PerspectiveCameraController::OnMouseButtonPressed));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(ZED_BIND_EVENT_FN(PerspectiveCameraController::OnMouseButtonReleased));
    }

    bool PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent& e){
        m_Camera.ProcessMouseScroll(static_cast<float>(e.GetYOffset()));
        return false;
    }

    bool PerspectiveCameraController::OnWindowsResized(WindowResizeEvent& e){
        // 目前存在问题，后面可以改为修改视锥体大小
        return false;
    }

    bool PerspectiveCameraController::OnMouseMoved(MouseMovedEvent& e){
        if(m_MouseMoveRestrictPressed){
            float xpos = static_cast<float>(e.GetX());
            float ypos = static_cast<float>(e.GetY());

            if (m_FirstMouse)
            {
                lastX = xpos;
                lastY = ypos;
                m_FirstMouse = false;
            }

            float xoffset = xpos - lastX;
            float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

            lastX = xpos;
            lastY = ypos;

            m_Camera.ProcessMouseMovement(xoffset, yoffset);
        }
        return false;
    }

    bool PerspectiveCameraController::OnMouseButtonPressed(MouseButtonPressedEvent& e){
        if(e.GetMouseButton() == m_MouseMoveRestrict){
            m_MouseMoveRestrictPressed = true;
            m_FirstMouse = true;
        }
        return false;
    }

    bool PerspectiveCameraController::OnMouseButtonReleased(MouseButtonReleasedEvent& e){
        if(e.GetMouseButton() == m_MouseMoveRestrict){
            m_MouseMoveRestrictPressed = false;
        }
        return false;
    }

}