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
		DC_PROFILE_FUNCTION
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		DC_CORE_ASSERT(status, "Can't init GLAD")

		DC_CORE_INFO("OpenGL Info:")
		DC_CORE_INFO("	Vender:{0}", (const char*)glGetString(GL_VENDOR))
		DC_CORE_INFO("	GPU:{0}", (const char*)glGetString(GL_RENDERER))
		DC_CORE_INFO("	Version:{0}", (const char*)glGetString(GL_VERSION))	
		auto extentions = GetExtensionInfos();

		if (extentions.size() > 0)
		{
			//DC_CORE_INFO("	Extensions:")
			//for (std::string extension : extentions)
			//{
			//	DC_CORE_INFO("		{0}", extension)
			//}
		}

	}

	std::vector<std::string> OpenGLContext::GetExtensionInfos() const
	{
		std::vector<std::string> g_supportExtensions;
		GLint n, i;
		glGetIntegerv(GL_NUM_EXTENSIONS, &n);
		for (i = 0; i < n; i++) {
			std::string extension = (char*)glGetStringi(GL_EXTENSIONS, i);
			g_supportExtensions.push_back(extension);
		}
		return g_supportExtensions;
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
