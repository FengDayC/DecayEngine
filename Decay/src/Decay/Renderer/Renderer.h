#pragma once
#include "Decay\Renderer\RenderCommand.h"


namespace Decay
{
	class Scene;
	class Shader;
	class DECAY_API Renderer
	{
	public:
		static void Init();
		static void BeginScene(const S_PTR<Scene>& scene);
		static void EndScene();
		static void Submit(const S_PTR<Shader>& shader,const S_PTR<VertexArray>& vertexArray,const glm::mat4& transform = glm::mat4(1.0f));
		static void OnWindowResize(uint32_t width, uint32_t height);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		static S_PTR<Scene>& s_Scene;
	};
}
