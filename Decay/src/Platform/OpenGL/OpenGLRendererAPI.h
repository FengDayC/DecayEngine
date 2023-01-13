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
        virtual void DrawIndexed(const S_PTR<VertexArray>& vertexArray) const override;
    };
}
