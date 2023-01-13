#include "dcpch.h"
#include "Texture.h"
#include "Platform\OpenGL\OpenGLTexture.h"
#include "Decay\Renderer\Renderer.h"

namespace Decay
{
	S_PTR<Texture2D> Decay::Texture2D::Create(const std::string path)
	{
		RendererAPI::API api = Renderer::GetAPI();
		DC_CORE_ASSERT((uint32_t)api, "No Renderer API");
		switch (api)
		{
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		}
		return nullptr;
	}
}
