#include <Genesis.h>

class Sandbox : public Genesis::Application
{
public:
	Sandbox()
	{
		
	}

	~Sandbox()
	{
		
	}
};

Genesis::Application* Genesis::CreateApplication()
{
	return new Sandbox();
}