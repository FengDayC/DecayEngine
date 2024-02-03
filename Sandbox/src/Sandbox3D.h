#include "Decay.h"

class Sandbox3D : public Decay::Layer
{
public:
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Decay::Timestep deltaTime) override;
	void OnImGuiRender() override;
	void OnEvent(Decay::Event& e) override;

private:
	S_PTR<Decay::Scene> mainScene;
};