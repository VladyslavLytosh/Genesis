#include <Genesis.h>

class Sandbox : public Genesis::Application
{
public:
	Sandbox()
	{
		PushLayer(new Genesis::ImGuiLayer());
	}

	~Sandbox()
	{
		
	}
};

Genesis::Application* Genesis::CreateApplication()
{
	return new Sandbox();
}