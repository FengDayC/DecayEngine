#include "dcpch.h"
#include "OpenGLTexture.h"
#include <stb_image.h>
#include "Decay\Profile\Instrumentor.hpp"
#include "Renderer\Texture.h"

namespace Decay
{
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) : m_Width(width), m_Height(height), m_ImageFormat(ImageFormat::RGBA)
	{
		DC_PROFILE_FUNCTION

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
		glTextureStorage2D(m_RendererId, 1, GL_RGBA8, m_Width, m_Height);
		glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;
		
	}
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, ImageFormat colorFormat)
		: m_Width(width), m_Height(height), m_ImageFormat(colorFormat)
	{
		switch (m_ImageFormat)
		{
		case ImageFormat::R:
			m_InternalFormat = GL_R8;
			m_DataFormat = GL_RED;
			break;
		case ImageFormat::RG:
			m_InternalFormat = GL_RG16;
			m_DataFormat = GL_RG;
		case ImageFormat::RGB:
			m_InternalFormat = GL_RGB8;
			m_DataFormat = GL_RGB;
			break;
		case ImageFormat::RGBA:
			m_InternalFormat = GL_RGBA8;
			m_DataFormat = GL_RGBA;
			break;
		default:
			DC_CORE_ASSERT(false, "Format not support!");
		}
	
	}
	OpenGLTexture2D::OpenGLTexture2D(const std::string path) : m_Path(path)
	{
		DC_PROFILE_FUNCTION
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

		switch (nrComponents)
		{
		case 1:
			m_InternalFormat = GL_R8;
			m_DataFormat = GL_RED;
			m_ImageFormat = ImageFormat::R;
			break;
		case 2:
			m_InternalFormat = GL_RG16;
			m_DataFormat = GL_RG;
			m_ImageFormat = ImageFormat::RG;
		case 3:
			m_InternalFormat = GL_RGB8;
			m_DataFormat = GL_RGB;
			m_ImageFormat = ImageFormat::RGB;
			break;
		case 4:
			m_InternalFormat = GL_RGBA8;
			m_DataFormat = GL_RGBA;
			m_ImageFormat = ImageFormat::RGBA;
			break;
		default:
			DC_CORE_ASSERT(false, "Format not support!");
		}

		DC_CORE_ASSERT(m_InternalFormat & m_DataFormat, "Format not support!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
		glTextureStorage2D(m_RendererId, 1, m_InternalFormat, m_Width, m_Height);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T,GL_REPEAT);
		glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
		glGenerateTextureMipmap(m_RendererId);

		stbi_image_free(data);
	}

	OpenGLTexture2D::OpenGLTexture2D(ImageFormat colorFormat, uint32_t width, uint32_t height, void* data) : m_ImageFormat(colorFormat)
	{
		DC_PROFILE_FUNCTION
		int nrComponents;
		
		DC_CORE_ASSERT(data, "Image data should not be null");

		m_Width = width;
		m_Height = height;

		switch (colorFormat)
		{
		case ImageFormat::R:
			m_InternalFormat = GL_R8;
			m_DataFormat = GL_RED;
			break;
		case ImageFormat::RG:
			m_InternalFormat = GL_RG16;
			m_DataFormat = GL_RG;
			break;
		case ImageFormat::RGB:
			m_InternalFormat = GL_RGB8;
			m_DataFormat = GL_RGB;
			break;
		case ImageFormat::RGBA:
			m_InternalFormat = GL_RGBA8;
			m_DataFormat = GL_RGBA;
			break;
		default:
			DC_CORE_ASSERT(false, "Format not support!");
		}

		DC_CORE_ASSERT(m_InternalFormat & m_DataFormat, "Format not support!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
		glTextureStorage2D(m_RendererId, 1, m_InternalFormat, m_Width, m_Height);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T,GL_REPEAT);
		glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
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
	
	ImageFormat OpenGLTexture2D::GetImageFormat()
	{
		return m_ImageFormat;
	}
}