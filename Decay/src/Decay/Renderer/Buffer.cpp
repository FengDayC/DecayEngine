#include "dcpch.h"
#include "Buffer.h"
#include "Decay\Renderer\Renderer.h"
#include "Platform\OpenGL\OpenGLBuffer.h"

namespace Decay
{
	VertexBuffer* VertexBuffer::Create(std::vector<float> vertices)
	{
		RendererAPI api = Renderer::GetAPI();
		DC_CORE_ASSERT((uint32_t)api, "No Renderer API");
		switch (api)
		{
		case RendererAPI::OpenGL :
			return new OpenGLVertexBuffer(vertices);
		}
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(std::vector<uint32_t> indices)
	{
		RendererAPI api = Renderer::GetAPI();
		DC_CORE_ASSERT((uint32_t)api, "No Renderer API");
		switch (api)
		{
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices);
		}
		return nullptr;
	}
}