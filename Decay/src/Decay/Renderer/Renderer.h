#pragma once
#include "Decay\Renderer\RenderCommand.h"

namespace Decay
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();
		static void Submit(const S_PTR(VertexArray)& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}
