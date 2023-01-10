#pragma once
#include "Decay/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Decay
{
    class OpenGLContext :
        public GraphicsContext
    {
    public :
        OpenGLContext(GLFWwindow* windowHandle);

        void Init() override;

        void SwapBuffers() override;

    private :
        GLFWwindow* m_WindowHandle;
    };
}
