#pragma once
#include <glm/glm.hpp>
#include "Texture.h"

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
		
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const S_PTR<Texture2D>& texture = nullptr);
		
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const S_PTR<Texture2D>& texture = nullptr);

	private:
	};


	struct Renderer2DData
	{
		S_PTR<Decay::VertexArray> VertexArray;
		S_PTR<Decay::ShaderLibrary> ShaderLib;
		S_PTR<Decay::Texture2D> WhiteTexture;
	};

	static U_PTR<Renderer2DData> s_Data;
}

