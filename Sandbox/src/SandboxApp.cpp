#include <Decay.h>
#include <memory>

class TestLayer : public Decay::Layer
{
public:
	TestLayer() : Layer("TestLayer")
	{

	}

	~TestLayer() override
	{
		DC_INFO("TestLayer Destroyed");
	}

	void OnAttach() override
	{
		DC_INFO("TestLayer Attached!");
	}
	void OnDetach() override
	{
		DC_INFO("TestLayer Detached!");
	}
	
	void OnUpdate() override
	{
		DC_INFO("TestLayer Update!");
	
	}
	
	void OnEvent(Decay::Event& e) override
	{
		DC_INFO("TestLayer Event!");
	}
};

class Sandbox : public Decay::Application
{
public:
	Sandbox()
	{
		PushLayer(new TestLayer());
	}

	~Sandbox()
	{

	}
};

S_PTR(Decay::Application) Decay::CreateApplication()
{
	return std::move(std::make_shared<Sandbox>());
}