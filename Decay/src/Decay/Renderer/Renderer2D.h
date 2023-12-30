#pragma once
#include <glm/glm.hpp>
#include "Texture.h"

namespace Decay
{
	class Scene;
	class VertexArray;
	class VertexBuffer;
	class ShaderLibrary;
	class Renderer2D
	{
	public:
		static void Init();

		static void Shutdown();

		static void BeginScene(S_PTR<Scene> scene);

		static void EndScene();

		static void Flush();
		
		static void DrawQuad(const glm::vec3& position, const float angle, const glm::vec2& size, const glm::vec4& color, const S_PTR<Texture2D>& texture = nullptr, const float tilling = 1.0f);
		
		static void DrawQuad(const glm::vec2& position, const float angle, const glm::vec2& size, const glm::vec4& color, const S_PTR<Texture2D>& texture = nullptr, const float tilling = 1.0f);

	private:
	};

	struct QuadVertex
	{
		glm::vec3 Pos;
		glm::vec4 Color;
		glm::vec2 UV;
		float TextureIndex;
		float Tilling;
	};

	struct Renderer2DData
	{
		const uint32_t MaxQuads = 1000;
		const uint32_t MaxVertices = 4 * MaxQuads;
		const uint32_t MaxIndices = 6 * MaxQuads;
		static const uint32_t MaxTextureSlots = 32;

		S_PTR<Decay::VertexArray> VertexArray;
		S_PTR<Decay::VertexBuffer> VertexBuffer;
		S_PTR<Decay::ShaderLibrary> ShaderLib;
		S_PTR<Decay::Texture2D> WhiteTexture;

		std::vector<QuadVertex> Vertices;
		std::array<S_PTR<Texture2D>, MaxTextureSlots> TextureSlots;
		glm::vec4 quads[4];

		uint32_t IndexCount = 0;
		float TextureSlotIndex = 1.0f;
	};
}

