#include "dcpch.h"
#include "Renderer.h"
#include "Decay\Profile\Instrumentor.hpp"
#include "Shader.h"
#include "Camera.h"
#include "FrameBuffer.h"
#include "Material.h"
#include "Texture.h"
#include "Decay\Scene\Mesh.h"
#include "Decay\Scene\Entity.hpp"
#include "Decay\Scene\Scene.h"
#include "Decay\Scene\Components.hpp"

namespace Decay
{
	static void ClearStatisticData(Statistic& stat)
	{
		stat.DrawCalls = 0;
		stat.TriangleCount = 0;
	}

	static RendererData s_Data;

	void Renderer::Init(RendererProperties prop)
	{
		DC_PROFILE_FUNCTION
		RenderCommand::Init();

		//ShaderLib
		s_Data.ShaderLibrary = CreateS_PTR<ShaderLibrary>();
		s_Data.ShaderLibrary->Load("Assets/Shaders/PBR.glsl");

		//MeshArray
		s_Data.MeshVertexArray = VertexArray::Create();
		s_Data.MeshVertexBuffer = VertexBuffer::Create(RendererData::MaxVertexCount * sizeof(Vertex));
		s_Data.BatchIndices = std::array<Index, RendererData::MaxTriangleCount>();
		{
			BufferLayout layout =
			{
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float3, "a_TexCood"},
				{ShaderDataType::Float3, "a_Normal"},
				{ShaderDataType::Float3, "a_Bitangent"},
				{ShaderDataType::Float3, "a_Tangent"}
			};
			s_Data.MeshVertexBuffer->SetLayout(layout);
		}

		//FrameBuffers
		s_Data.FrameBuffers.clear();
		for (int i = 0; i < prop.FramebufferCount; i++)
		{
			S_PTR<FrameBuffer> frameBuffer = FrameBuffer::Create(prop.Width, prop.Height, prop.FramebufferAttrib);
			frameBuffer->Clear();
			s_Data.FrameBuffers.push_back(frameBuffer);
		}

		//Stat
		ClearStatisticData(s_Data.Stats);
	}

	void Renderer::BeginFrame()
	{
		DC_PROFILE_FUNCTION
		s_Data.NowFrameBuffer = s_Data.FrameBuffers.front();
		s_Data.NowFrameBuffer->Bind();
	}

	void Renderer::EndFrame()
	{
		DC_PROFILE_FUNCTION
		s_Data.FrameBuffers.pop_front();
		s_Data.FrameBuffers.push_back(s_Data.NowFrameBuffer);
		s_Data.NowFrameBuffer = nullptr;

		ClearStatisticData(s_Data.Stats);
	}

	void Renderer::BeginScene(S_PTR<Scene> scene)
	{
		DC_PROFILE_FUNCTION
		s_Data.NowScene = scene;
	}

	void Renderer::EndScene()
	{
		DC_PROFILE_FUNCTION
		s_Data.NowScene = nullptr;
	}

	void Renderer::SubmitMesh(Mesh& mesh, const glm::mat4& transform)
	{
		DC_PROFILE_FUNCTION
		S_PTR<MeshSource> meshSource = mesh.GetMeshSource();
		std::vector<Submesh> subMeshes = meshSource->GetSubmeshes();
		std::vector<S_PTR<Material>> materials = meshSource->GetMaterials();
		std::vector<Vertex> vertices = meshSource->GetVertices();
		std::vector<Index> indices = meshSource->GetIndices();
		for (Submesh subMesh : subMeshes)
		{
			DC_CORE_ASSERT(subMesh.VertexCount <= RendererData::MaxVertexCount, "Vertex Count is too large!");
			if(subMesh.VertexCount + s_Data.VertexCount > RendererData::MaxVertexCount)
			{
				Flush();
			}
			else
			{
				s_Data.Materials[s_Data.MaterialCount++] = materials[subMesh.MaterialIndex];
				std::copy(vertices.begin() + subMesh.BaseVertex
					, vertices.begin() + subMesh.BaseVertex + subMesh.VertexCount
					, s_Data.BatchVertices.begin() + s_Data.VertexCount);
				s_Data.VertexCount += subMesh.VertexCount;
				std::copy(indices.begin() + subMesh.BaseIndex
					, indices.begin() + subMesh.BaseIndex + subMesh.IndexCount
					, s_Data.BatchIndices.begin() + s_Data.IndexCount);
				s_Data.IndexCount += subMesh.IndexCount;
			}
		}
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::SetClearColor(const glm::vec4& color)
	{
		for (S_PTR<FrameBuffer> frameBuffer : s_Data.FrameBuffers)
		{
			frameBuffer->SetClearColor(color);
		}
	}

	void Renderer::SetClearDepth(const float depth)
	{
		for (S_PTR<FrameBuffer> frameBuffer : s_Data.FrameBuffers)
		{
			frameBuffer->SetClearDepth(depth);
		}
	}

	void Renderer::SetClearStencil(const uint32_t stencil)
	{
		for (S_PTR<FrameBuffer> frameBuffer : s_Data.FrameBuffers)
		{
			frameBuffer->SetClearStencil(stencil);
		}
	}

	void Renderer::Clear()
	{
		for (S_PTR<FrameBuffer> frameBuffer : s_Data.FrameBuffers)
		{
			frameBuffer->Clear();
		}
	}
	
	void Renderer::Flush()
	{
		DC_CORE_ASSERT(s_Data.VertexCount >= 3, "Vertex count must be over 3");
		s_Data.MeshVertexBuffer->SetData(s_Data.BatchVertices.data(), s_Data.VertexCount);
		S_PTR<IndexBuffer> indexBuffer = IndexBuffer::Create(s_Data.IndexCount);
		s_Data.MeshVertexArray->SetIndexBuffer(indexBuffer);
		indexBuffer->SetData(s_Data.BatchIndices.data(), s_Data.IndexCount);

		Entity cameraEntity = s_Data.NowScene->GetMainCameraEntity();
		Camera camera = cameraEntity.GetComponent<CameraComponent>().OriginCamera;
		TransformComponent cameraTransform = cameraEntity.GetComponent<TransformComponent>();

		for (int i = 0; i < s_Data.MaterialCount; i++)
		{
			auto& material = s_Data.Materials[i];
			material->Bind();
			material->Set("decay_camera_matrix", camera.CalculateMatrix(cameraTransform.Position, cameraTransform.Rotation));
		}
		RenderCommand::DrawIndexed(s_Data.MeshVertexArray, s_Data.IndexCount);

		s_Data.VertexCount = 0;
		s_Data.IndexCount = 0;
		s_Data.MaterialCount = 0;
		s_Data.Stats.DrawCalls++;
	}

	S_PTR<ShaderLibrary> Renderer::GetShaderLibrary()
	{
		return s_Data.ShaderLibrary;
	}
}