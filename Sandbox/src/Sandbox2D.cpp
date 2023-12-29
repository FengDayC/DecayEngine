#include "Sandbox2D.h"
#include <ImGui/imgui.h>
#include <Platform/OpenGL/OpenGLShader.h>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

using namespace Decay;

Sandbox2D::Sandbox2D() : Layer("Sandbox2D")
{
	m_CameraController = CameraController::GetDefaultOrthographicController(16.0f / 9.0f);
	m_Scene = std::make_shared<Scene>(m_CameraController);
}

void Sandbox2D::OnAttach()
{
	m_Texture = Texture2D::Create("assets/texture/UV_Checker.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Decay::Timestep deltaTime)
{
	DC_PROFILE_FUNCTION();

	{
		DC_PROFILE_SCOPE("OnUpdate");
		m_Scene->GetSceneCameraController()->OnUpdate(deltaTime);
	}

	{
		DC_PROFILE_SCOPE("Renderer Preparation");
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RenderCommand::Clear();
	}

	{
		DC_PROFILE_SCOPE("Renderer Draw");
		Renderer2D::BeginScene(m_Scene);

		Renderer2D::DrawQuad({ -0.5f, 0.0f, -0.1f }, { 0.5f, 0.3f }, m_SquareColor);
		Renderer2D::DrawQuad({ 0.3f, 0.0f, 0.0f}, { 1.0f, 1.0f }, m_SquareColor, m_Texture);

		Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	DC_PROFILE_FUNCTION();
	ImGui::Begin("Test");
	ImGui::Text("Test Window");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Decay::Event& e)
{
	m_Scene->GetSceneCameraController()->OnEvent(e);
}
