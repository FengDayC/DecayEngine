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

        std::vector<std::string> GetExtensionInfos() const;

    private :
        GLFWwindow* m_WindowHandle;
    };
}
