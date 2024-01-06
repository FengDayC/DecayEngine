#include "dcpch.h"
#include "OpenGLTexture.h"
#include <stb_image.h>
#include "Decay\Profile\Instrumentor.hpp"
#include "Renderer\Texture.h"

namespace Decay
{
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) : m_Width(width), m_Height(height)
	{
		DC_PROFILE_FUNCTION();

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
		glTextureStorage2D(m_RendererId, 1, GL_RGBA8, m_Width, m_Height);
		glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;
		
	}
	OpenGLTexture2D::OpenGLTexture2D(const std::string path) : m_Path(path)
	{
		DC_PROFILE_FUNCTION();
		int width, height, nrComponents;
		stbi_uc* data = nullptr;
		{
			DC_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string) ");
			stbi_set_flip_vertically_on_load(true);
			data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
		}
		DC_CORE_ASSERT(data, "Cannot load image!");

		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, format = 0;
		switch (nrComponents)
		{
		case 1:
			internalFormat = GL_R8;
			format = GL_RED;
			break;
		case 3:
			internalFormat = GL_RGB8;
			format = GL_RGB;
			break;
		case 4:
			internalFormat = GL_RGBA8;
			format = GL_RGBA;
			break;
		}

		DC_CORE_ASSERT(internalFormat & format, "Format not support!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
		glTextureStorage2D(m_RendererId, 1, internalFormat, m_Width, m_Height);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T,GL_REPEAT);
		glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, format, GL_UNSIGNED_BYTE, data);
		glGenerateTextureMipmap(m_RendererId);

		stbi_image_free(data);
	}

	OpenGLTexture2D::OpenGLTexture2D(ImageFormat colorFormat, uint32_t width, uint32_t height, void* data)
	{
		DC_PROFILE_FUNCTION();
		int nrComponents;
		
		DC_CORE_ASSERT(data, "Image data should not be null");

		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, format = 0;
		switch (colorFormat)
		{
		case ImageFormat::R:
			internalFormat = GL_R8;
			format = GL_RED;
			break;
		case ImageFormat::RGB:
			internalFormat = GL_RGB8;
			format = GL_RGB;
			break;
		case ImageFormat::RGBA:
			internalFormat = GL_RGBA8;
			format = GL_RGBA;
			break;
		}

		DC_CORE_ASSERT(internalFormat & format, "Format not support!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
		glTextureStorage2D(m_RendererId, 1, internalFormat, m_Width, m_Height);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T,GL_REPEAT);
		glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, format, GL_UNSIGNED_BYTE, data);
		glGenerateTextureMipmap(m_RendererId);

	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererId);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererId);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		uint32_t byteperpixel = m_DataFormat == GL_RGBA ? 4 : 3;
		DC_CORE_ASSERT(size == m_Width * m_Height * byteperpixel, "Data must be entire texture!");
		glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

}