#include <Genesis.h>

class ExampleLayer : public Genesis::Layer
{
public:
	ExampleLayer()
		: Layer("ExampleLayer")
	{
		
	}

	void OnUpdate() override
	{
	}

	void OnEvent(Genesis::Event& event) override
	{
		GS_INFO("ExampleLayer::OnEvent {0}", event);
	}
};

class Sandbox : public Genesis::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
		
	}
};

Genesis::Application* Genesis::CreateApplication()
{
	return new Sandbox();
}