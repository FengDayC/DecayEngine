#include "dcpch.h"
#include "Renderer.h"
#include "Decay\Renderer\Shader.h"
#include "Decay\Scene\Scene.h"
#include "Platform\OpenGL\OpenGLShader.h"
#include "Decay\Profile\Instrumentor.hpp"
#include "Renderer2D.h"
#include "Camera.h"
#include "Scene\Mesh.h"
#include "FrameBuffer.h"

namespace Decay
{
	static U_PTR<RendererData> s_Data = std::make_unique<RendererData>();

	void Renderer::Init()
	{
		DC_PROFILE_FUNCTION
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::BeginFrame()
	{
		DC_PROFILE_FUNCTION
		s_Data->NowFrameBuffer = s_Data->FrameBuffers.front();
	}

	void Renderer::EndFrame()
	{
		s_Data->FrameBuffers.pop_front();
		s_Data->FrameBuffers.push_back(s_Data->NowFrameBuffer);
	}

	void Renderer::BeginScene(const Camera& camera)
	{
		s_Data->Camera = camera;
	}

	void Renderer::EndScene()
	{
		
	}

	void Renderer::SubmitMesh(Mesh& mesh, const glm::mat4& transform)
	{
		DC_PROFILE_FUNCTION
		auto meshSource = mesh.GetMeshSource();
		auto subMeshes = meshSource->GetSubmeshes();
		auto meterials = meshSource->GetMaterials();
		for (auto subMesh : subMeshes)
		{
			auto& material = meterials[subMesh.MaterialIndex];

		}
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::SetClearColor(const glm::vec4& color)
	{
		for (auto frameBuffer : s_Data->FrameBuffers)
		{
			frameBuffer.SetClearColor(color);
		}
	}

	void Renderer::SetClearDepth(const float depth)
	{
		for (auto frameBuffer : s_Data->FrameBuffers)
		{
			frameBuffer.SetClearDepth(depth);
		}
	}

	void Renderer::SetClearStencil(const uint32_t stencil)
	{
		for (auto frameBuffer : s_Data->FrameBuffers)
		{
			frameBuffer.SetClearStencil(stencil);
		}
	}

	void Renderer::Clear()
	{
		for (auto frameBuffer : s_Data->FrameBuffers)
		{
			frameBuffer.Clear();
		}
	}

	W_PTR<ShaderLibrary> Renderer::GetShaderLibrary()
	{
		return CreateW_PTR<ShaderLibrary>(s_Data->ShaderLibrary);
	}
}