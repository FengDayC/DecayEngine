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
			return CreateS_PTR<OpenGLVertexBuffer>(vertices);
		}
		return nullptr;
	}

	S_PTR<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		RendererAPI::API  api = Renderer::GetAPI();
		DC_CORE_ASSERT((uint32_t)api, "No Renderer API");
		switch (api)
		{
		case RendererAPI::API::OpenGL :
			return CreateS_PTR<OpenGLVertexBuffer>(size);
		}
		return nullptr;
	}

	S_PTR<IndexBuffer> IndexBuffer::Create(S_PTR<std::vector<uint32_t>> indices)
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