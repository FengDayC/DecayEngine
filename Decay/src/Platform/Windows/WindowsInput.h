#pragma once
#include "Decay/Input.h"

namespace Decay
{
    class WindowsInput :
        public Input
    {
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;
        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual PAIR(float, float) GetMousePosImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
    };
}



