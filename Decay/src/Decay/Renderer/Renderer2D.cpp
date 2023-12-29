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

	uint32_t whiteData = 0xffffffff;
	s_Data->WhiteTexture = Texture2D::Create(1, 1);
	s_Data->WhiteTexture->SetData(&whiteData, sizeof(uint32_t));

	std::vector<float> vertices
	{
		-.5f,-.5f,-.1f, .0f, .0f,
		-.5f,.5f,-.1f, .0f, 1.0f,
		.5f,.5f,-.1f, 1.0f, 1.0f,
		.5f,-.5f,-.1f,	1.0f, .0f
	};

	auto vertexBuffer = VertexBuffer::Create(vertices);

	{
		BufferLayout layout =
		{
			{ShaderDataType::Float3,"a_Pos"},
			{ShaderDataType::Float2,"a_UV"},
		};

		vertexBuffer->SetLayout(layout);
	}

	std::vector<uint32_t> indices{ 0,1,2,3,0,2 };
	auto indexBuffer = IndexBuffer::Create(indices);

	s_Data->VertexArray->AddVertexBuffer(vertexBuffer);
	s_Data->VertexArray->SetIndexBuffer(indexBuffer);

	s_Data->ShaderLib = CreateS_PTR<ShaderLibrary>();
	s_Data->ShaderLib->Load("assets/shaders/Texture.glsl");
}

void Decay::Renderer2D::Shutdown()
{
	s_Data.release();
}

void Decay::Renderer2D::BeginScene(S_PTR<Scene> scene)
{
	S_PTR<Shader> textureShader = s_Data->ShaderLib->Get("Texture");
	textureShader ->Bind();
	textureShader ->SetMatrix4("decay_camera_viewMatrix", scene->GetSceneCameraController()->GetCamera().GetViewMatrix());
	textureShader ->SetMatrix4("decay_camera_projectionMatrix", scene->GetSceneCameraController()->GetCamera().GetProjectionMatrix());
}

void Decay::Renderer2D::EndScene()
{
}

void Decay::Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const S_PTR<Texture2D>& texture)
{
	S_PTR<Shader> textureShader = s_Data->ShaderLib->Get("Texture");
	textureShader->Bind();

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::scale(glm::mat4(1.0f), { size.x,size.y,1.0f });
	
	textureShader->SetMatrix4("decay_model_transform", transform);
	textureShader->SetInt("u_texture", 0);
	textureShader->SetFloat4("u_color", color);
	textureShader->SetFloat("u_textureScale", 1.0f);

	if (texture)
	{
		texture->Bind(0);
	}
	else
	{
		s_Data->WhiteTexture->Bind(0);
	}

	s_Data->VertexArray->Bind();
	RenderCommand::DrawIndexed(s_Data->VertexArray);
}

void Decay::Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const S_PTR<Texture2D>& texture)
{
	DrawQuad(glm::vec3(position, 0.0f), size , color , texture);
}
