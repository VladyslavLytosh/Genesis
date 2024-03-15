#pragma once
#include "../Genesis.h"

#ifdef GS_PLATFORM_WINDOWS

int main(int argc, char** argv)
{
	auto app = Genesis::CreateApplication();
	app->Run();
	delete app;
}

#endif