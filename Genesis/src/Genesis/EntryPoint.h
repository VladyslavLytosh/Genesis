#pragma once

#ifdef GS_PLATFORM_WINDOWS
int main(int argc, char** argv)
{
    Genesis::Log::Init();
    GS_CORE_WARN("Init log!");

    auto app = Genesis::CreateApplication();
    app->Run();
    delete app;
}
#endif