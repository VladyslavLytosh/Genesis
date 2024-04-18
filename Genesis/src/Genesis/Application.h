#pragma once

#include "Core.h"
#include "Window.h"
#include "Genesis/LayerStack.h"
#include "Genesis/Events/ApplicationEvent.h"

#include "Genesis/ImGui/ImGuiLayer.h"
#include "Renderer/Shader.h"

namespace Genesis
{
	/**
	 * \brief Abstract representation of Engine app itself.
	 * Can be inherited in client application, to add additional functionality
	 * \remark The Application class is a singleton. It is created by the CLIENT,
	 * and if we attempt to create more than one instance, we will encounter an assertion.
	 * \remark The lifetime of the window,layer stack (WILL BE CONTINUED) is tied to the Application.
	 */
	class GENESIS_API Application
	{
	public:
		Application();
		virtual ~Application();
		/**
		 * \brief Runs the game loop (until the game is stopped).
		 */
		void Run();
		/**
		 * \brief Application class handles all callbacks(e.g windows callback) and propagate it, down to the layers
		 * \param event Incoming event to process
		 * \remark Besides broadcasting events to layers, the Application class can also handle incoming events itself.
		 */
		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() const { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;
		// We cache the ImGuiLayer because we need the ability to call its functions separately from the layer stack.
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
		static Application* s_Instance;
	};

	/**
	 * \brief To be defined on CLIENT
	 */
	Application* CreateApplication();
}
