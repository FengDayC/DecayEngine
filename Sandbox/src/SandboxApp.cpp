#include <Decay.h>
#include <memory>

class Sandbox : public Decay::Application
{
public:
	Sandbox()
	{
		PushOverlay(new Decay::ImGuiLayer());
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