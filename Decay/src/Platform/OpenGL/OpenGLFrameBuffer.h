#include "Renderer\FrameBuffer.h"
#include <glm\glm.hpp>

namespace Decay
{
	class OpenGLTexture2D;

	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(uint32_t width, uint32_t height, FrameBufferAttrib attrib);
		~OpenGLFrameBuffer() override;

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual void Clear() override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void SetClearDepth(float depth) override;
		virtual void SetClearStencil(uint32_t stencil) override;

		virtual uint32_t GetWidth() const override;
		virtual uint32_t GetHeight() const override;

	private:
		uint32_t m_RendererID;
		S_PTR<OpenGLTexture2D> m_ColorAttachment;
		S_PTR<OpenGLTexture2D> m_DepthAttachment;
		S_PTR<OpenGLTexture2D> m_StencilAttachment;
		uint32_t m_Width;
		uint32_t m_Height;
		uint32_t m_SizePerPixel;
	};
}
