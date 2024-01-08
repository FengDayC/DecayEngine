#include "dcpch.h"
#include "Renderer2D.h"
#include "Scene.h"
#include "VertexArray.h"
#include "Shader.h"
#include <Platform/OpenGL/OpenGLShader.h>
#include "RenderCommand.h"
#include <Decay/Profile/Instrumentor.hpp>

static Decay::Renderer2DData s_Data;

void Decay::Renderer2D::Init()
{
	s_Data.VertexArray = VertexArray::Create();
	s_Data.VertexBuffer = VertexBuffer::Create(s_Data.MaxVertices*sizeof(QuadVertex));
	s_Data.Vertices = std::vector<QuadVertex>();

	uint32_t whiteData = 0xffffffff;
	s_Data.WhiteTexture = Texture2D::Create(1, 1);
	s_Data.WhiteTexture->SetData(&whiteData, sizeof(uint32_t));

	{
		BufferLayout layout =
		{
			{ShaderDataType::Float3,"a_pos"},
			{ShaderDataType::Float4,"a_color"},
			{ShaderDataType::Float2,"a_uv"},
			{ShaderDataType::Float,"a_textureIndex"},
			{ShaderDataType::Float,"a_tilling"}
		};

		s_Data.VertexBuffer->SetLayout(layout);
	}

	S_PTR<std::vector<uint32_t>> indices = CreateS_PTR<std::vector<uint32_t>>();
	uint32_t offset = 0;
	for (int i = 0; i < s_Data.MaxIndices; i+=6)
	{
		indices->push_back(offset);
		indices->push_back(offset + 1);
		indices->push_back(offset + 2);
		indices->push_back(offset + 2);
		indices->push_back(offset + 3);
		indices->push_back(offset);
		offset+=4;
	}
	auto indexBuffer = IndexBuffer::Create(indices);

	s_Data.VertexArray->SetVertexBuffer(s_Data.VertexBuffer);
	s_Data.VertexArray->SetIndexBuffer(indexBuffer);

	s_Data.TextureSlots = std::array<S_PTR<Texture2D>, Renderer2DData::MaxTextureSlots>();
	s_Data.TextureSlots[0] = s_Data.WhiteTexture;

	s_Data.ShaderLib = CreateS_PTR<ShaderLibrary>();
	s_Data.ShaderLib->Load("assets/shaders/2DQuad.glsl");

	s_Data.quads[0] = { -0.5f,-0.5f,0.0f,1.0f };
	s_Data.quads[1] = { 0.5f,-0.5f,0.0f,1.0f };
	s_Data.quads[2] = { 0.5f,0.5f,0.0f,1.0f };
	s_Data.quads[3] = { -0.5f,0.5f,0.0f,1.0f };
}

void Decay::Renderer2D::Shutdown()
{
}

void Decay::Renderer2D::BeginScene(S_PTR<Scene> scene)
{
	S_PTR<Shader> textureShader = s_Data.ShaderLib->Get("2DQuad");
	textureShader->Bind();
	textureShader->SetMatrix4("decay_camera_viewMatrix", scene->GetSceneCameraController()->GetCamera().GetViewMatrix());
	textureShader->SetMatrix4("decay_camera_projectionMatrix", scene->GetSceneCameraController()->GetCamera().GetProjectionMatrix());

	s_Data.Vertices.clear();
	s_Data.TextureSlotIndex = 1;
	s_Data.IndexCount = 0;
}

void Decay::Renderer2D::EndScene()
{
	s_Data.VertexBuffer->SetData(s_Data.Vertices.data(), s_Data.Vertices.size() * sizeof(QuadVertex));
	Flush();
	s_Data.Stats.DrawCalls++;
}

void Decay::Renderer2D::Flush()
{
	for (uint32_t i = 0; i < (uint32_t)s_Data.TextureSlotIndex; i++)
	{
		s_Data.TextureSlots[i]->Bind(i);
	}
	RenderCommand::DrawIndexed(s_Data.VertexArray, s_Data.IndexCount);
}

void Decay::Renderer2D::DrawQuad(const glm::vec3& position, const float angle, const glm::vec2& size, const glm::vec4& color, const S_PTR<Texture2D>& texture, const float tilling)
{
	DC_PROFILE_FUNCTION

	if (s_Data.IndexCount >= Renderer2DData::MaxIndices)
	{
		Renderer2D::StartNewBatch();
	}

	float textureIndex = .0f;
	if (texture)
	{
		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if (*texture == *(s_Data.TextureSlots[i]))
			{
				textureIndex = (float)i;
			}
		}
		if (textureIndex == .0f)
		{
			textureIndex = s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex += 1.0f;
		}
	}
	else
	{
		textureIndex = .0f;
	}

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3{ .0f,.0f,1.0f })
		* glm::scale(glm::mat4(1.0f), glm::vec3{ size.x,size.y,1.0f });

	s_Data.Vertices.push_back({ transform * s_Data.quads[0], color, {.0f,.0f}, textureIndex, tilling});
	s_Data.Vertices.push_back({ transform * s_Data.quads[1], color, {1.0f,.0f}, textureIndex, tilling});
	s_Data.Vertices.push_back({ transform * s_Data.quads[2], color, {1.0f,1.0f}, textureIndex, tilling});
	s_Data.Vertices.push_back({ transform * s_Data.quads[3], color, {.0f,1.0f}, textureIndex, tilling});
	s_Data.IndexCount += 6;

	int* samplers = new int[s_Data.TextureSlots.size()];
	for (int i = 0; i < s_Data.TextureSlots.size(); i++)
	{
		samplers[i] = i;
	}
	s_Data.ShaderLib->Get("2DQuad")->SetIntArray("u_textures", samplers, s_Data.TextureSlots.size());
	delete samplers;

	s_Data.Stats.QuadCount++;
}

void Decay::Renderer2D::DrawQuad(const glm::vec2& position, const float angle, const glm::vec2& size, const glm::vec4& color, const S_PTR<Texture2D>& texture, const float tilling)
{
	DrawQuad(glm::vec3(position, 0.0f), angle, size , color , texture, tilling);
}

void Decay::Renderer2D::ResetStats()
{
	memset(&s_Data.Stats, 0, sizeof(Statistic));
}

Decay::Renderer2D::Statistic Decay::Renderer2D::GetStats()
{
	return s_Data.Stats;
}

void Decay::Renderer2D::StartNewBatch()
{
	EndScene();

	s_Data.Vertices.clear();
	s_Data.TextureSlotIndex = 1;
}
