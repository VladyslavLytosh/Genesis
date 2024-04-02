#pragma once

#include "Genesis/Core.h"
#include "Genesis/KeyCodes.h"
#include "Genesis/MouseButtonCodes.h"

namespace Genesis
{
	class GENESIS_API Input
	{
	public:
		static bool IsKeyPressed(KeyCode keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(KeyCode keycode) const = 0;

		virtual bool IsMouseButtonPressedImpl(MouseCode button) const = 0;
		virtual std::pair<float, float> GetMousePositionImpl() const = 0;
		virtual float GetMouseXImpl() const = 0;
		virtual float GetMouseYImpl() const = 0;

	private:
		static std::unique_ptr<Input> s_Instance;
	};
}
