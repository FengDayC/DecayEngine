#pragma once
#include "Decay\Renderer\RendererAPI.h"
#include "Renderer.h"

namespace Decay
{
	class DECAY_API RenderCommand
	{
	public:		

		static void Init()
		{
			s_RendererAPI->Init();
		}

		static void DrawIndexed(const S_PTR<VertexArray>& vertexArray, const uint32_t size = 0)
		{
			s_RendererAPI->DrawIndexed(vertexArray,size);
		}
		
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}
