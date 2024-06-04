#pragma once

#include "Zed/Events/MouseEvent.h"
#include "Zed/Events/ApplicationEvent.h"
#include "Zed/Core/Timestep.h"
#include "Zed/Camera/PerspectiveCamera.h"

namespace Zed {
    class PerspectiveCameraController {
    public:
        PerspectiveCameraController(glm::vec3 cameraPosition);
        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);

        PerspectiveCamera& GetCamera(){return m_Camera;}
        const PerspectiveCamera& GetCamera() const {return m_Camera;}

        glm::mat4 GetViewMatrix(){
            return m_Camera.GetViewMatrix();
        }
    
        glm::mat4 GetProjectionMatrix(){
            glm::mat4 projection =
                glm::perspective(glm::radians(m_Camera.Zoom), (float)1200 / (float)800, 0.1f, 100.0f);
            return projection;
        }

    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowsResized(WindowResizeEvent& e);
        bool OnMouseMoved(MouseMovedEvent& e);
        bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);

    private:
        PerspectiveCamera m_Camera;
        MouseCode m_MouseMoveRestrict = Mouse::ButtonRight;
        bool m_MouseMoveRestrictPressed = false;
        bool m_FirstMouse = true;
        float lastX, lastY;
    };

}