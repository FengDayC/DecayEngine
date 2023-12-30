#pragma once
#include "Decay\Renderer\Buffer.h"

namespace Decay
{
    class OpenGLVertexBuffer :
        public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(uint32_t size);
        OpenGLVertexBuffer(std::vector<float> vertices);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const override;
        virtual void UnBind() const override;

        virtual void SetLayout(const BufferLayout& layout) override;
        virtual const BufferLayout& GetLayout() const override;
        virtual void SetData(const void* data, uint32_t size) override;

    private:
        uint32_t m_RendererId;

        BufferLayout m_Layout;
    };

    class OpenGLIndexBuffer :
        public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(S_PTR<std::vector<uint32_t>> vertices);
        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const override;
        virtual void UnBind() const override;

        inline virtual uint32_t GetCount() const override { return m_Count; }

    private:
        uint32_t m_RendererId;

        uint32_t m_Count;
    };
}
