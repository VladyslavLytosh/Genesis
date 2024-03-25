#pragma once

#include "Core.h"
#include "Window.h"
#include "Genesis/Events/ApplicationEvent.h"

namespace Genesis
{
	class GENESIS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);

	private:
		bool OnWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
