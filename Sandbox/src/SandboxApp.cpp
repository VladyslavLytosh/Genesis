#include <Genesis.h>

class ExampleLayer : public Genesis::Layer
{
public:
	virtual void OnUpdate() override
	{
		
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