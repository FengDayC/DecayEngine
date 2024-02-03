#include "dcpch.h"
#include "FrameBuffer.h"
#include "RendererAPI.h"
#include "Renderer.h"
#include "Platform\OpenGL\OpenGLFrameBuffer.h"

namespace Decay
{
	S_PTR<FrameBuffer> FrameBuffer::Create(uint32_t width, uint32_t height, uint64_t props)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			DC_CORE_ERROR("No Renderer API");
			break;
		case RendererAPI::API::OpenGL:
			return CreateS_PTR<OpenGLFrameBuffer>(width, height, props);

		default:
			DC_CORE_ERROR("Unsupported Renderer API");
			break;
		}
		return nullptr;
	}
}
