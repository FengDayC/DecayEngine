#include "dcpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform\OpenGL\OpenGLVertexArray.h"

namespace Decay
{
	S_PTR<VertexArray> VertexArray::Create()
	{
		RendererAPI::API api = Renderer::GetAPI();
		DC_CORE_ASSERT((uint32_t)api, "No Renderer API");
		switch (api)
		{
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		}
		return nullptr;
	}
}