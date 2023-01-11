#include "dcpch.h"
#include "RenderCommand.h"
#include "Platform\OpenGL\OpenGLRendererAPI.h"

namespace Decay
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}