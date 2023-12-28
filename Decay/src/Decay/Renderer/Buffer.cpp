#include "dcpch.h"
#include "Buffer.h"
#include "Decay\Renderer\Renderer.h"
#include "Platform\OpenGL\OpenGLBuffer.h"

namespace Decay
{
	S_PTR<VertexBuffer> VertexBuffer::Create(std::vector<float> vertices)
	{
		RendererAPI::API  api = Renderer::GetAPI();
		DC_CORE_ASSERT((uint32_t)api, "No Renderer API");
		switch (api)
		{
		case RendererAPI::API::OpenGL :
			return std::make_shared<OpenGLVertexBuffer>(vertices);
		}
		return nullptr;
	}

	S_PTR<IndexBuffer> IndexBuffer::Create(std::vector<uint32_t> indices)
	{
		RendererAPI::API api = Renderer::GetAPI();
		DC_CORE_ASSERT((uint32_t)api, "No Renderer API");
		switch (api)
		{
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLIndexBuffer>(indices);
		}
		return nullptr;
	}
}