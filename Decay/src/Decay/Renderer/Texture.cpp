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
}
