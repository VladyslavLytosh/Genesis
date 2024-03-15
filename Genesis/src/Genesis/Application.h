#pragma once

#include "Core.h"

namespace Genesis
{
	class GENESIS_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}