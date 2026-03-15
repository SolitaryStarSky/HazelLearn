#include <Hazel.h>

class Sandbox :public HL::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

HL::Application* HL::CreateApplication()
{
	return new Sandbox();
}