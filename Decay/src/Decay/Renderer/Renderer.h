#pragma once
#include "Decay\Renderer\RenderCommand.h"
#include "Scene\Mesh.h"

namespace Decay
{
	class Camera;
	class ShaderLibrary;
	class Scene;
	class Shader;
	class Mesh;
	class FrameBuffer;
	struct RendererInitProperties;
	class DECAY_API Renderer
	{
	public:
		static void Init();
		static void BeginFrame();
		static void EndFrame();
		static void BeginScene(const Camera& camera);
		static void EndScene();
		static void SubmitMesh(Mesh& mesh, const glm::mat4& transform = glm::mat4(1.0f));

	public:
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void SetClearColor(const glm::vec4& color);
		static void SetClearDepth(const float depth);
		static void SetClearStencil(const uint32_t stencil);
		static void Clear();
		static inline W_PTR<ShaderLibrary> GetShaderLibrary();

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};

	struct RendererData
	{
		static const uint32_t MaxVertexCount = 8192;
		static const uint32_t MaxIndexCount = 8192 * 6;

		U_PTR<ShaderLibrary> ShaderLibrary;
		S_PTR<Scene> Scene;
		Camera& Camera;

		//FrameBuffers
		FrameBuffer& NowFrameBuffer;
		std::list<FrameBuffer> FrameBuffers;

		Statistic Stats;
		S_PTR<VertexArray> MeshVertexArray;
		S_PTR<VertexBuffer> MeshVertexBuffer;

		//Batch Rendering
		uint32_t VertexCount = 0;
		std::vector<Vertex> BatchVertices;
		std::vector<Index> BatchIndices;
	};

	struct Statistic
	{
		int DrawCalls = 0;
		int QuadCount = 0;

		int GetTotalVertexCount() { return QuadCount * 4; };
		int GetTotalIndexCount() { return QuadCount * 6; };
	};

	struct RendererInitProperties
	{
		uint32_t framebufferCount;
	};

}
