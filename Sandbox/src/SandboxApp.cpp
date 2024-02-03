#include <Decay.h>
#include <Decay\Core\EntryPoint.h>
#include "Sandbox3D.h"

using namespace Decay;

class Sandbox : public Decay::Application
{
public:
	Sandbox()
	{
		PushLayer(new Sandbox3D());
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