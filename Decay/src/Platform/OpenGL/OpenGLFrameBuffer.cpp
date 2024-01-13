#include "dcpch.h"
#include "OpenGLFrameBuffer.h"
#include "OpenGLTexture.h"
#include "glad\glad.h"

Decay::OpenGLFrameBuffer::OpenGLFrameBuffer(uint32_t width, uint32_t height, FrameBufferAttrib attrib)
	: m_ColorAttachment(0),m_DepthAttachment(0),m_StencilAttachment(0),m_Width(width),m_Height(height)
{
	glGenFramebuffers(1, &m_RendererID);
	m_SizePerPixel = 0;
	uint32_t intAttrib = ((uint32_t)attrib);
	uint32_t colorAttrib = (intAttrib) & 0x7;
	DC_CORE_ASSERT(colorAttrib - LOWBIT(colorAttrib) == 0, "Only one color attachment attribution is supported!");
	switch (colorAttrib)
	{
	case BIT(0):
		m_SizePerPixel += 1;
		m_ColorAttachment = CreateS_PTR<OpenGLTexture2D>(width, height, ImageFormat::R);
		break;
	case BIT(1):
		m_SizePerPixel += 3;
		m_ColorAttachment = CreateS_PTR<OpenGLTexture2D>(width, height, ImageFormat::RGB);
		break;
	case BIT(2):
		m_SizePerPixel += 4;
		m_ColorAttachment = CreateS_PTR<OpenGLTexture2D>(width, height, ImageFormat::RGBA);
		break;
	}
	intAttrib >>= 3;
	uint32_t depthAttrib = (intAttrib) & 0xf;
	DC_CORE_ASSERT(depthAttrib - LOWBIT(depthAttrib) == 0, "Only one depth attachment attribution is supported!");
	switch (depthAttrib)
	{
	case BIT(0):
		m_SizePerPixel += 1;
		m_DepthAttachment = CreateS_PTR<OpenGLTexture2D>(width, height, ImageFormat::R);
		break;
	case BIT(1):
		m_SizePerPixel += 2;
		m_DepthAttachment = CreateS_PTR<OpenGLTexture2D>(width, height, ImageFormat::RG);
		break;
	case BIT(2):
		m_SizePerPixel += 3;
		m_DepthAttachment = CreateS_PTR<OpenGLTexture2D>(width, height, ImageFormat::RGB);
		break;
	case BIT(3):
		m_SizePerPixel += 4;
		m_DepthAttachment = CreateS_PTR<OpenGLTexture2D>(width, height, ImageFormat::RGBA);
		break;
	}
	depthAttrib >>= 4;
	uint32_t stencilAttrib = (intAttrib) & 0xf;
	DC_CORE_ASSERT(stencilAttrib - LOWBIT(stencilAttrib ) == 0, "Only one attachment attribution is supported!");
	switch (stencilAttrib)
	{
	case BIT(0):
		m_SizePerPixel += 1;
		m_StencilAttachment = CreateS_PTR<OpenGLTexture2D>(width, height, ImageFormat::R);
		break;
	case BIT(1):
		m_SizePerPixel += 2;
		m_StencilAttachment = CreateS_PTR<OpenGLTexture2D>(width, height, ImageFormat::RG);
		break;
	case BIT(2):
		m_SizePerPixel += 3;
		m_StencilAttachment = CreateS_PTR<OpenGLTexture2D>(width, height, ImageFormat::RGB);
		break;
	case BIT(3):
		m_SizePerPixel += 4;
		m_StencilAttachment = CreateS_PTR<OpenGLTexture2D>(width, height, ImageFormat::RGBA);
		break;
	}
}

Decay::OpenGLFrameBuffer::~OpenGLFrameBuffer()
{
}

void Decay::OpenGLFrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
}

void Decay::OpenGLFrameBuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Decay::OpenGLFrameBuffer::Resize(uint32_t width, uint32_t height)
{
	m_Width = width;
	m_Height = height;
	m_ColorAttachment = CreateS_PTR<OpenGLTexture2D>(width, height, m_ColorAttachment->GetImageFormat());
	m_DepthAttachment = CreateS_PTR<OpenGLTexture2D>(width, height, m_DepthAttachment->GetImageFormat());
	m_StencilAttachment = CreateS_PTR<OpenGLTexture2D>(width, height, m_StencilAttachment->GetImageFormat());
}

void Decay::OpenGLFrameBuffer::Clear()
{
	Bind();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
	Unbind();
}

void Decay::OpenGLFrameBuffer::SetClearColor(const glm::vec4& color)
{
	Bind();
	glClearColor(color.r, color.g, color.b, color.a);
	Unbind();
}

void Decay::OpenGLFrameBuffer::SetClearDepth(float depth)
{
	Bind();
	glClearDepth(depth);
	Unbind();
}

void Decay::OpenGLFrameBuffer::SetClearStencil(uint32_t stencil)
{
	Bind();
	glClearStencil(stencil);
	Unbind();
}

uint32_t Decay::OpenGLFrameBuffer::GetWidth() const
{
	return m_Width;
}

uint32_t Decay::OpenGLFrameBuffer::GetHeight() const
{
	return m_Height;
}
