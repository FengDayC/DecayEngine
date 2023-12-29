#pragma once
#include <glm/glm.hpp>

namespace Decay
{
	class Scene;
	class VertexArray;
	class ShaderLibrary;
	class Renderer2D
	{
	public:
		static void Init();

		static void Shutdown();

		static void BeginScene(S_PTR<Scene> scene);

		static void EndScene();

		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
	};


	struct Renderer2DData
	{
		S_PTR<Decay::VertexArray> VertexArray;
		S_PTR<Decay::ShaderLibrary> ShaderLib;
	};

	static U_PTR<Renderer2DData> s_Data;
}

