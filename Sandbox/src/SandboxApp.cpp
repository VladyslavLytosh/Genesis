#include <Genesis.h>

class ExampleLayer : public Genesis::Layer
{
public:
	virtual void OnUpdate() override
	{
		if (Genesis::Input::IsKeyPressed(Genesis::Key::Tab))
		{
			GS_INFO("Tab is pressed");
		}
	}

	virtual void OnEvent(Genesis::Event& event) override
	{
		
	}
};

class Sandbox : public Genesis::Application
{
public:
	Sandbox()
	{
		PushLayer(new Genesis::ImGuiLayer());
		PushLayer(new ExampleLayer());
	}

	virtual ~Sandbox() override
	{
		
	}
};

Genesis::Application* Genesis::CreateApplication()
{
	return new Sandbox();
}