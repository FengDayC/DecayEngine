#pragma once
#include "Decay\Renderer\RendererAPI.h"

namespace Decay
{
    class OpenGLRendererAPI :
        public RendererAPI
    {
    public:
        virtual void Init() override;
        virtual void SetClearColor(const glm::vec4& color) const override;
        virtual void Clear() const override;
        virtual void DrawIndexed(const S_PTR<VertexArray>& vertexArray, const uint32_t size = 0) const override;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const override;
    };
}
