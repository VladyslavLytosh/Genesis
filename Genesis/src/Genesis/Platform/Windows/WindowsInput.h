#pragma once

#include "Genesis/Input.h"

namespace Genesis
{
    class WindowsInput : public Input
    {
      protected:
        virtual bool IsKeyPressedImpl(KeyCode keycode) const override;

        virtual bool IsMouseButtonPressedImpl(MouseCode button) const override;
        virtual std::pair<float, float> GetMousePositionImpl() const override;
        virtual float GetMouseXImpl() const override;
        virtual float GetMouseYImpl() const override;
    };
}  // namespace Genesis