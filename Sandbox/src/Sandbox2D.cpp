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
	m_VertexArray = VertexArray::Create();

	std::vector<float> vertices
	{
		-.5f,-.5f,-.1f,
		-.5f,.5f,-.1f,
		.5f,.5f,-.1f,
		.5f,-.5f,-.1f,
	};

	m_VertexBuffer = VertexBuffer::Create(vertices);

	{
		BufferLayout layout =
		{
			{ShaderDataType::Float3,"a_Pos"},
		};

		m_VertexBuffer->SetLayout(layout);
	}

	std::vector<uint32_t> indices{ 0,1,2,3,0,2 };
	m_IndexBuffer = IndexBuffer::Create(indices);

	m_VertexArray->AddVertexBuffer(m_VertexBuffer);
	m_VertexArray->SetIndexBuffer(m_IndexBuffer);

	m_ShaderLib.Load("assets/shaders/FlatColor.glsl");
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
		DC_PROFILE_SCOPE("Renderer Prepare");
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RenderCommand::Clear();
	}

	{
		DC_PROFILE_SCOPE("Renderer Draw");
		Renderer::BeginScene(m_Scene);

		std::dynamic_pointer_cast<OpenGLShader>(m_ShaderLib.Get("FlatColor"))->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(m_ShaderLib.Get("FlatColor"))->SetUniformFloat4("flatColor", m_SquareColor);
		Renderer::Submit(m_ShaderLib.Get("FlatColor"), m_VertexArray);

		Renderer::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Test");
	ImGui::Text("Test Window");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Decay::Event& e)
{
	m_Scene->GetSceneCameraController()->OnEvent(e);
}
