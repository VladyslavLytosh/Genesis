#pragma once

#include "Genesis/Input.h"

namespace Genesis
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) const override;

		virtual bool IsMouseButtonPressedImpl(int button) const override;
		virtual std::pair<float, float> GetMousePositionImpl() const override;
		virtual float GetMouseXImpl() const override;
		virtual float GetMouseYImpl() const override;
	};
}