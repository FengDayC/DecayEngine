#pragma once
#include "Decay\Renderer\FrameBuffer.h"

namespace Decay
{
	class OpenGLTexture2D;

	class OpenGLFrameBuffer : public Decay::FrameBuffer
	{
	public:
		OpenGLFrameBuffer(uint32_t width, uint32_t height, uint64_t props);
		virtual ~OpenGLFrameBuffer();

		void Bind() override;
		void Unbind() override;

		void Resize(uint32_t width, uint32_t height) override;

		void Clear() override;

		void SetClearColor(const glm::vec4& color) override;
		void SetClearDepth(float depth) override;
		void SetClearStencil(uint32_t stencil) override;

		uint32_t GetWidth() const override;
		uint32_t GetHeight() const override;

	private:
		uint32_t m_RendererID;
		S_PTR<OpenGLTexture2D> m_ColorAttachment;
		S_PTR<OpenGLTexture2D> m_DepthAttachment;
		S_PTR<OpenGLTexture2D> m_StencilAttachment;
		uint32_t m_Width;
		uint32_t m_Height;
		uint32_t m_SizePerPixel;
		uint64_t m_FrameBufferProps;
	};
}
