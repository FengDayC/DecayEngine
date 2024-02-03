#pragma once
#include <glm\glm.hpp>

namespace Decay
{
	enum class FrameBufferAttrib
	{
		COLOR_R = BIT(0),
		COLOR_RGB = BIT(1),
		COLOR_RGBA = BIT(2),
		DEPTH_8 = BIT(3),
		DEPTH_16 = BIT(4),
		DEPTH_24 = BIT(5),
		DEPTH_32 = BIT(6),
		STENCIL_8 = BIT(7),
		STENCIL_16 = BIT(8),
		STENCIL_24 = BIT(9),
		STENCIL_32 = BIT(10),
	};

	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() {};

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual void Clear() = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void SetClearDepth(float depth) = 0;
		virtual void SetClearStencil(uint32_t stencil) = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

	public:
		static S_PTR<FrameBuffer> Create(uint32_t width, uint32_t height, uint64_t props);
	};
}