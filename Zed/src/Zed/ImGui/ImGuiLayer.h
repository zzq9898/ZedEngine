#pragma once

#include "Zed/Core/Layer.h"
namespace Zed {
    class ImGuiLayer : public Layer{
    public:
        ImGuiLayer();
        ~ImGuiLayer() override;

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event &event) override;
    private:
        float m_Time = 0.0f;
    };
}