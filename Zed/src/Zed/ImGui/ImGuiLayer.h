#pragma once

#include "Zed/Core/Layer.h"
namespace Zed {
    class ImGuiLayer : public Layer{
    public:
        ImGuiLayer();
        ~ImGuiLayer() override;

        void OnAttach() override;
        void OnDetach() override;
        virtual void OnImGuiRender() override;
        void Begin();
        void End();
    private:
        float m_Time = 0.0f;
    };
}