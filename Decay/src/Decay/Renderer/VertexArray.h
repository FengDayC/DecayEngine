#pragma once
#include "Decay\Renderer\Buffer.h"

namespace Decay
{
	class DECAY_API VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual void AddVertexBuffer(S_PTR<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(S_PTR<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<S_PTR<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const S_PTR<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};
}