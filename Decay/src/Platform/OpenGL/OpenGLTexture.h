#pragma once
#include "Decay\Renderer\Texture.h"
#include "glad\glad.h"

namespace Decay
{
	enum class ImageFormat;

	class OpenGLTexture2D : public Texture2D
	{
	public:

		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string path);
		OpenGLTexture2D(ImageFormat colorFormat, uint32_t width, uint32_t height, void* data);

		virtual ~OpenGLTexture2D();

		inline virtual uint32_t GetWidth() const override { return m_Width; }
		inline virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void Bind(uint32_t slot = 0) const override;

		virtual void SetData(void* data, uint32_t size) override;

		virtual bool operator==(const Texture& other) const override
		{
			return m_RendererId == ((OpenGLTexture2D&)other).m_RendererId;
		}

	private:
		std::string m_Path;

		uint32_t m_Width;
		uint32_t m_Height;

		uint32_t m_RendererId;

		GLenum m_InternalFormat, m_DataFormat;
	};
}
