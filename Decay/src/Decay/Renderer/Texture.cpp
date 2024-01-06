#include "dcpch.h"
#include "Texture.h"
#include "Platform\OpenGL\OpenGLTexture.h"
#include "Decay\Renderer\Renderer.h"

namespace Decay
{
	S_PTR<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		RendererAPI::API api = Renderer::GetAPI();
		DC_CORE_ASSERT((uint32_t)api, "No Renderer API");
		switch (api)
		{
		case RendererAPI::API::None:
			DC_CORE_ASSERT(false, "No Renderer API");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateS_PTR<OpenGLTexture2D>(width, height);
		}
		return S_PTR<Texture2D>();
	}
	S_PTR<Texture2D> Decay::Texture2D::Create(const std::string path)
	{
		RendererAPI::API api = Renderer::GetAPI();
		DC_CORE_ASSERT((uint32_t)api, "No Renderer API");
		switch (api)
		{
		case RendererAPI::API::None:
			DC_CORE_ASSERT(false, "No Renderer API");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateS_PTR<OpenGLTexture2D>(path);
		}
		return nullptr;
	}
	S_PTR<Texture2D> Texture2D::Create(ImageFormat colorFormat,uint32_t width, uint32_t height, void* data)
	{
		RendererAPI::API api = Renderer::GetAPI();
		switch (api)
		{
		case RendererAPI::API::None:
			DC_CORE_ASSERT(false, "No Renderer API");
		case RendererAPI::API::OpenGL:
			return CreateS_PTR<OpenGLTexture2D>(colorFormat, width, height, data);
		}

		return nullptr;
	}
	S_PTR<Texture> Texture2D::GetWhite()
	{
		RendererAPI::API api = Renderer::GetAPI();
		uint32_t whiteData = 0xffffffff;
		switch (api)
		{
		case RendererAPI::API::None:
			DC_CORE_ASSERT(false, "No Renderer API");
		case RendererAPI::API::OpenGL:
			return CreateS_PTR<OpenGLTexture2D>(ImageFormat::RGBA, 1, 1, &whiteData);
		}

		return nullptr;
	}
}
