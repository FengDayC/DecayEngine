#pragma once
#include "Decay\Renderer\RendererAPI.h"

namespace Decay
{
	class DECAY_API RenderCommand
	{
	public:		

		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}
		
		inline static void DrawIndexed(const S_PTR<VertexArray>& vertexArray, const uint32_t size = 0)
		{
			s_RendererAPI->DrawIndexed(vertexArray,size);
		}
		
		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}
