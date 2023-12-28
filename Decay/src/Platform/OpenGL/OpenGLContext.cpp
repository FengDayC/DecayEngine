#include "dcpch.h"
#include "OpenGLContext.h"
#include "Decay\Profile\Instrumentor.hpp"
#include <glad\glad.h>
#include <GLFW\glfw3.h>

namespace Decay
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) 
	{
		DC_CORE_ASSERT(windowHandle, "Window is nullptr!");
	}

	void OpenGLContext::Init()
	{
		DC_PROFILE_FUNCTION();
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		DC_CORE_ASSERT(status, "Can't init GLAD");

		DC_CORE_INFO("OpenGL Info:");
		DC_CORE_INFO("	Vender:{0}", (const char*)glGetString(GL_VENDOR));
		DC_CORE_INFO("	GPU:{0}", (const char*)glGetString(GL_RENDERER));
		DC_CORE_INFO("	Version:{0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
