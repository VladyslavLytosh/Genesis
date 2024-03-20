#include "gspch.h"

#include "Application.h"
#include "Log.h"
#include "Events/ApplicationEvent.h"

namespace Genesis
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(800, 600);
		GS_TRACE(e);
		while (true)
		{
			
		}
	}
}