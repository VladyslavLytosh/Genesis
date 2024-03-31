#pragma once

#include "Genesis/Layer.h"
#include "Genesis/Events/ApplicationEvent.h"
#include "Genesis/Events/KeyEvent.h"
#include "Genesis/Events/MouseEvent.h"

namespace Genesis
{
	class GENESIS_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		virtual ~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;

	private:
		float m_Time = 0.0f;

		bool OnMouseMovedEvent(MouseMovedEvent& event);
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& event);
		bool OnKeyPressedEvent(KeyPressedEvent& event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& event);
		bool OnWindowResizeEvent(WindowResizeEvent& event);
		bool OnKeyTypedEvent(KeyTypedEvent& event);
	};
}
