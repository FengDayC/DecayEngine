#pragma once
#include <Decay.h>

class Sandbox2D : public Decay::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Decay::Timestep deltaTime) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Decay::Event& e) override;

private:

	S_PTR<Decay::CameraController> m_CameraController;
	S_PTR<Decay::Scene> m_Scene;

	S_PTR<Decay::Texture2D> m_Texture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	
};

