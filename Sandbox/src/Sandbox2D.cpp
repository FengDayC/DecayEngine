#include "Sandbox2D.h"
#include <ImGui\imgui.h>
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
	m_Texture = Texture2D::Create("Assets/Textures/UV_Checker.png");
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

	Renderer2D::ResetStats();
	{
		DC_PROFILE_SCOPE("Renderer Draw");
		Renderer2D::BeginScene(m_Scene);

		Renderer2D::DrawQuad({ -0.5f, 0.0f, -0.1f }, 45.0f, { 0.5f, 0.3f }, m_SquareColor);
		Renderer2D::DrawQuad({ 0.3f, 0.0f, 0.0f}, .0f, { 1.0f, 1.0f }, {1.0f,1.0f,1.0f,1.0f}, m_Texture, 10.0f);

		Renderer2D::EndScene();

		Renderer2D::BeginScene(m_Scene);

		static float rotateAngle = .0f;

		rotateAngle += deltaTime * 50.0f;
		if (rotateAngle > 360.0f)
		{
			rotateAngle -= 360.0f;
		}
		for (float x = -5.0f; x < 5.0f; x += 0.5f)
		{
			for (float y = -5.0f; y < 5.0f; y += 0.5f)
			{
				glm::vec2 rg = { (x + 5.0f) / 10.0f,(x + 5.0f) / 10.0f };
				Renderer2D::DrawQuad({ x, y, -0.05f }, rotateAngle, { 0.3f, 0.3f }, { rg.r*0.8f + 0.2f,rg.g,0.5f,0.4f });
			}
		}

		Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	DC_PROFILE_FUNCTION();
	ImGui::Begin("Test");
	ImGui::Text("Renderer Stat");
	auto rendererStat = Renderer2D::GetStats();
	ImGui::Text("Draw Calls:%d", rendererStat.DrawCalls);
	ImGui::Text("Quads:%d", rendererStat.QuadCount);
	ImGui::Text("Vertices:%d", rendererStat.GetTotalVertexCount());
	ImGui::Text("Indices:%d", rendererStat.GetTotalIndexCount());
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Decay::Event& e)
{
	m_Scene->GetSceneCameraController()->OnEvent(e);
}
