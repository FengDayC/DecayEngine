#pragma once
#include "Decay\Renderer\VertexArray.h"

namespace Decay
{
    class OpenGLVertexArray :
        public VertexArray
    {
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual void AddVertexBuffer(S_PTR<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(S_PTR<IndexBuffer>& indexBuffer) override;

		virtual inline const std::vector<S_PTR<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
		virtual inline const S_PTR<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

	private:
		std::vector<S_PTR<VertexBuffer>> m_VertexBuffers;
		S_PTR<IndexBuffer> m_IndexBuffer;
		uint32_t m_RendererId;
    };
}
