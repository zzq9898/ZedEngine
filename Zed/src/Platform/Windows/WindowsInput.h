#pragma once

#include "Zed/Core/Input.h"

namespace Zed {

    class WindowsInput : public Input{
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;
        virtual std::pair<float, float> GetMousePositionImpl()override;
        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
    };
}