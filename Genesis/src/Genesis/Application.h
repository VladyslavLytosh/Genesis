#pragma once

#include "Core.h"
#include "Window.h"
#include "Genesis/LayerStack.h"
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

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() const { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
