#include "dcpch.h"
#include "OpenGLTexture.h"
#include <stb_image.h>
#include <glad\glad.h>

namespace Decay
{

	OpenGLTexture2D::OpenGLTexture2D(const std::string path) : m_Path(path)
	{
		int width, height, nrComponents;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
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
		glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, format, GL_UNSIGNED_BYTE, data);
		glGenerateTextureMipmap(m_RendererId);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererId);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererId);
	}

}