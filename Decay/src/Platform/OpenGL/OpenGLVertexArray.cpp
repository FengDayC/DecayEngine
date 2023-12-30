#include "dcpch.h"
#include "OpenGLVertexArray.h"
#include <glad\glad.h>
#include "Decay\Profile\Instrumentor.hpp"

namespace Decay
{


	GLenum ShaderDataType2OpenGLType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Bool:
		case ShaderDataType::Bool2:
		case ShaderDataType::Bool3:
		case ShaderDataType::Bool4:
			return GL_BOOL;
		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4:
		case ShaderDataType::Mat2:
		case ShaderDataType::Mat3:
		case ShaderDataType::Mat4:
			return GL_FLOAT;
		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4:
			return GL_INT;
		}

		DC_CORE_ASSERT(false, "Unkown shader type");

		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererId);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererId);
	}

	void OpenGLVertexArray::Bind() const
	{
		DC_PROFILE_FUNCTION();
		glBindVertexArray(m_RendererId);
	}

	void OpenGLVertexArray::UnBind() const
	{
		DC_PROFILE_FUNCTION();
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::SetVertexBuffer(S_PTR<VertexBuffer>& vertexBuffer)
	{
		DC_PROFILE_FUNCTION();
		DC_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex layout hasn't been set!");

		glBindVertexArray(m_RendererId);
		vertexBuffer->Bind();

		int index = 0;
		for (auto& element : vertexBuffer->GetLayout())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataType2OpenGLType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				vertexBuffer->GetLayout().GetStride(),
				(const void*)element.Offset
			);
			index++;
		}

		m_VertexBuffers.clear();
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(S_PTR<IndexBuffer>& indexBuffer)
	{
		DC_PROFILE_FUNCTION();
		glBindVertexArray(m_RendererId);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}