#pragma once

#ifdef GS_PLATFORM_WINDOWS

int main(int argc, char** argv)
{
	Genesis::Log::Init();
	GS_CORE_WARN("Init log!");
	int a = 5;
	GS_INFO("Hello! Var={0}", a);

	auto app = Genesis::CreateApplication();
	app->Run();
	delete app;
}

#endif