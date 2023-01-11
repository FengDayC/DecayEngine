#pragma once

namespace Decay
{
	enum class RendererAPI : uint32_t
	{
		None = 0,
		OpenGL = 1,
		Vulkan = 2,
		DirectX = 3
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};
}
