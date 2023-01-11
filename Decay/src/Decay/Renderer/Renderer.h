#pragma once
#include "Decay\Renderer\RenderCommand.h"


namespace Decay
{
	class Scene;
	class Shader;
	class Renderer
	{
	public:
		static void BeginScene(const S_PTR(Scene)& scene);
		static void EndScene();
		static void Submit(const S_PTR(Shader)& shader,const S_PTR(VertexArray)& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		static S_PTR(Scene)& s_Scene;
	};
}
