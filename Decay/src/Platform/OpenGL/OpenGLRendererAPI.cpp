#include "dcpch.h"
#include "OpenGLRendererAPI.h"
#include <glad\glad.h>

void Decay::OpenGLRendererAPI::SetClearColor(const glm::vec4& color) const
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void Decay::OpenGLRendererAPI::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Decay::OpenGLRendererAPI::DrawIndexed(const S_PTR(VertexArray)& vertexArray) const
{
	glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}
