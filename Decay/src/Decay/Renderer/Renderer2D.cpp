#include "dcpch.h"
#include "Renderer2D.h"
#include "Scene.h"
#include "VertexArray.h"
#include "Shader.h"
#include <Platform/OpenGL/OpenGLShader.h>
#include "RenderCommand.h"

void Decay::Renderer2D::Init()
{
	s_Data = CreateU_PTR<Renderer2DData>();

	s_Data->VertexArray = VertexArray::Create();

	std::vector<float> vertices
	{
		-.5f,-.5f,-.1f,
		-.5f,.5f,-.1f,
		.5f,.5f,-.1f,
		.5f,-.5f,-.1f,
	};

	auto vertexBuffer = VertexBuffer::Create(vertices);

	{
		BufferLayout layout =
		{
			{ShaderDataType::Float3,"a_Pos"},
		};

		vertexBuffer->SetLayout(layout);
	}

	std::vector<uint32_t> indices{ 0,1,2,3,0,2 };
	auto indexBuffer = IndexBuffer::Create(indices);

	s_Data->VertexArray->AddVertexBuffer(vertexBuffer);
	s_Data->VertexArray->SetIndexBuffer(indexBuffer);

	s_Data->ShaderLib = CreateS_PTR<ShaderLibrary>();
	s_Data->ShaderLib->Load("assets/shaders/FlatColor.glsl");

}

void Decay::Renderer2D::Shutdown()
{
	s_Data.release();
}

void Decay::Renderer2D::BeginScene(S_PTR<Scene> scene)
{
	S_PTR<Shader> flatColorShader = s_Data->ShaderLib->Get("FlatColor");
	flatColorShader->Bind();
	flatColorShader->SetMatrix4("decay_camera_viewMatrix", scene->GetSceneCameraController()->GetCamera().GetViewMatrix());
	flatColorShader->SetMatrix4("decay_camera_projectionMatrix", scene->GetSceneCameraController()->GetCamera().GetProjectionMatrix());
}

void Decay::Renderer2D::EndScene()
{
}

void Decay::Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
	S_PTR<Shader> flatColorShader = s_Data->ShaderLib->Get("FlatColor");
	flatColorShader->SetFloat4("flatColor", color);

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });

	flatColorShader->SetMatrix4("decay_model_transform", transform);

	s_Data->VertexArray->Bind();
	RenderCommand::DrawIndexed(s_Data->VertexArray);
}

void Decay::Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
	DrawQuad(glm::vec3(position, 0.0f), size, color);
}
