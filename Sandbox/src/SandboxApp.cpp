#include <Decay.h>
#include <memory>

class Sandbox : public Decay::Application
{
public:
	Sandbox()
	{
	}

	~Sandbox() override
	{
		DC_INFO("Sandbox Release!");
	}
};

void Decay::CreateApplication()
{
	new Sandbox();
}