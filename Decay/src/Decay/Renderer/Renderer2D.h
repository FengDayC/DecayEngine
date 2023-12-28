#pragma once
#include <glm/glm.hpp>

namespace Decay
{
	class Renderer2D
	{
	public:
		static void Init();

		static void Shutdown();

		static void BeginScene();

		static void EndScene();

		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	};
}

