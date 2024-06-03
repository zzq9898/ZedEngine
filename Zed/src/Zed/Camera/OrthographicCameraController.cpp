#include "OrthographicCameraController.h"
#include "Zed/Core/Input.h"
#include "Zed/Core/ZedKeyCodes.h"
#include "Zed/Core/Base.h"

namespace Zed {

    OrthographicCameraController::OrthographicCameraController(float aspecRato, bool rotation)
        : m_AspectRatio(aspecRato),
        m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
        m_Rotation(rotation)
    {}

    void OrthographicCameraController::OnUpdate(Timestep ts) {
        if (Zed::Input::IsKeyPressed(ZED_KEY_A))
            m_CameraPosition.x -= m_CameraMoveSpeed * ts;
        else if (Zed::Input::IsKeyPressed(ZED_KEY_D))
            m_CameraPosition.x += m_CameraMoveSpeed * ts ;

        if (Zed::Input::IsKeyPressed(ZED_KEY_W))
            m_CameraPosition.y += m_CameraMoveSpeed * ts ;
        else if (Zed::Input::IsKeyPressed(ZED_KEY_S))
            m_CameraPosition.y -= m_CameraMoveSpeed * ts ;

        if (m_Rotation) {
            if (Zed::Input::IsKeyPressed(ZED_KEY_Q))
                m_CameraRotation += m_CameraRotationSpeed * ts;
            if (Zed::Input::IsKeyPressed(ZED_KEY_E))
                m_CameraRotation -= m_CameraRotationSpeed * ts;
        }

        m_Camera.SetPosition(m_CameraPosition);
        m_CameraMoveSpeed = m_ZoomLevel;
    }

    void OrthographicCameraController::OnEvent(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(ZED_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizeEvent>(ZED_BIND_EVENT_FN(OrthographicCameraController::OnWindowsResized));
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent &e) {
        m_ZoomLevel -= e.GetYOffset() * 0.25;
        m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
        m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

    bool OrthographicCameraController::OnWindowsResized(WindowResizeEvent &e) {
        m_AspectRatio = (float)e.GetWidth()/(float)e.GetHeight();
        m_Camera.SetProjection(-m_AspectRatio*m_ZoomLevel, m_AspectRatio*m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
}