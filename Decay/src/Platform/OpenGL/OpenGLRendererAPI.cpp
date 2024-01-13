#include "dcpch.h"
#include "OpenGLRendererAPI.h"
#include <glad\glad.h>

namespace Decay
{
	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST|GL_STENCIL_TEST);
	}

	void OpenGLRendererAPI::DrawIndexed(const S_PTR<VertexArray>& vertexArray, const uint32_t size) const
	{
		if (size)
		{
			glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, nullptr);
		}
		else
		{
			glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		}
	}
	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const
	{
		glViewport(x, y, width, height);
	}
}
