#include <Decay.h>
#include <memory>

class Sandbox : public Decay::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

std::shared_ptr<Decay::Application> Decay::CreateApplication()
{
	return std::move(std::make_shared<Sandbox>());
}