#pragma once
#include <glm\glm.hpp>
#include "Decay\Renderer\VertexArray.h"

namespace Decay
{
	class DECAY_API RendererAPI
	{
	public:
		enum class API : uint32_t
		{
			None = 0,
			OpenGL = 1,
			Vulkan = 2,
			DirectX = 3
		};

	public:
		virtual void Init() = 0;
		virtual void SetClearColor(const glm::vec4& color) const = 0;
		virtual void Clear() const = 0;
		virtual void DrawIndexed(const S_PTR<VertexArray>& vertexArray, const uint32_t size = 0) const = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const = 0;

		static inline API GetAPI() { return s_API; }
	private:

		static API s_API;
	};
}
