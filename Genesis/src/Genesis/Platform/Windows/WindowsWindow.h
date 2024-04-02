#pragma once

#include "Genesis/Window.h"

#include <GLFW/glfw3.h>

namespace Genesis
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		unsigned GetWidth() const override { return m_Data.Width; }
		unsigned GetHeight() const override { return m_Data.Height; }

		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		virtual void* GetActualWindow() const override { return m_Window; }
	private:
		void Init(const WindowProps& props);
		void Shutdown();

		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}