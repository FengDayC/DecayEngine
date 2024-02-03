#pragma once
#include "Decay\Renderer\RenderCommand.h"
#include "Scene\Mesh.h"
#include "FrameBuffer.h"

namespace Decay
{
	class Camera;
	class ShaderLibrary;
	class Scene;
	class Shader;
	class Mesh;
	class FrameBuffer;
	class Texture2D;

	struct RendererProperties
	{
		uint32_t Width;
		uint32_t Height;
		uint32_t FramebufferCount;
		uint64_t FramebufferAttrib;
	};
	const RendererProperties DefaultRendererInitProperties
	{ 
		1920,
		1080,
		3,
		(uint64_t)FrameBufferAttrib::COLOR_RGBA|(uint64_t)FrameBufferAttrib::DEPTH_32
	};

	struct Statistic
	{
		int DrawCalls = 0;
		int TriangleCount = 0;
	};

	struct RendererData
	{
		static const uint32_t MaxTriangleCount = 1024;
		static const uint32_t MaxVertexCount = MaxTriangleCount * 3;
		static const uint32_t MaxMaterialSlots = 32;

		U_PTR<ShaderLibrary> ShaderLibrary;
		S_PTR<Scene> Scene;

		//FrameBuffers
		S_PTR<FrameBuffer> NowFrameBuffer;
		std::list<S_PTR<FrameBuffer>> FrameBuffers;

		//Stat
		Statistic Stats;

		//Rendering
		S_PTR<VertexArray> MeshVertexArray;
		S_PTR<VertexBuffer> MeshVertexBuffer;

		//Batch Rendering
		uint32_t VertexCount = 0;
		uint32_t IndexCount = 0;
		std::array<Vertex, RendererData::MaxVertexCount> BatchVertices;
		std::array<Index, RendererData::MaxTriangleCount> BatchIndices;

		//Material
		uint32_t MaterialCount = 0;
		std::array<S_PTR<Material>, RendererData::MaxMaterialSlots> Materials;
	};


	class DECAY_API Renderer
	{
	public:
		static void Init(RendererProperties prop = DefaultRendererInitProperties);
		static void BeginFrame();
		static void EndFrame();
		static void BeginScene(S_PTR<Scene> scene);
		static void EndScene();
		static void SubmitMesh(Mesh& mesh, const glm::mat4& transform = glm::mat4(1.0f));

	public:
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void SetClearColor(const glm::vec4& color);
		static void SetClearDepth(const float depth);
		static void SetClearStencil(const uint32_t stencil);
		static void Clear();
		static void Flush();
		static inline W_PTR<ShaderLibrary> GetShaderLibrary();

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	};

}
