#pragma once

#include "Event.h"
#include "Genesis/KeyCodes.h"

namespace Genesis
{
	class GENESIS_API KeyEvent : public Event
	{
	public:
		KeyCode GetKeyCode() const { return m_Keycode; }

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
	protected:
		KeyEvent(KeyCode keycode)
		: m_Keycode(keycode) {}

		KeyCode m_Keycode;
	};

	class GENESIS_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(KeyCode keycode, int repeatCount)
		: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_Keycode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class GENESIS_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(KeyCode keycode)
		: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_Keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class GENESIS_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(KeyCode keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_Keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}
