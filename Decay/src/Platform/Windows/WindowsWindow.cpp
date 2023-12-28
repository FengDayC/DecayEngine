#include "dcpch.h"
#include "WindowsWindow.h"
#include "Decay\Core\Window.h"
#include "Decay\Core\Events\ApplicationEvent.h"
#include "Decay\Core\Events\MouseEvent.h"
#include "Decay\Core\Events\KeyEvent.h"
#include "Decay\Input\Input.h"
#include "Platform\OpenGL\OpenGLContext.h"
#include "Decay\Profile\Instrumentor.hpp"

#include "glad\glad.h"
#include "GLFW\glfw3.h"

namespace Decay
{
#ifdef DECAY_PLATFORM_WINDOWS
	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}
#endif

	static bool s_GLFWInitialized = false;

	static void glfwErrorCallback(int code, const char* description)
	{
		DC_CORE_ERROR("glfw error:{0}:{1}", code, description);
	}

	WindowsWindow::WindowsWindow(WindowProps props)
	{
		DC_PROFILE_FUNCTION();
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Shutdown()
	{
		DC_PROFILE_FUNCTION();
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		DC_PROFILE_FUNCTION();
		m_Data.Title = props.Title;
		m_Data.height = props.Height;
		m_Data.width = props.Width;

		DC_CORE_INFO("Creating Window {0} ({1},{2})", props.Title, props.Width, props.Height);
	
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();

			glfwSetErrorCallback(glfwErrorCallback);

			DC_CORE_ASSERT(success, "GLFW initialize failed!")

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)m_Data.width, (int)m_Data.height, m_Data.Title.c_str(), nullptr, nullptr);

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		glfwSetWindowSizeCallback(m_Window, WindowResizeCallback);
		glfwSetWindowCloseCallback(m_Window, WindowCloseCallback);
		glfwSetKeyCallback(m_Window, WindowKeyCallback);
		glfwSetMouseButtonCallback(m_Window, WindowMouseButtonCallback);
		glfwSetScrollCallback(m_Window, WindowMouseScrollCallback);
		glfwSetCursorPosCallback(m_Window, WindowCursorPosCallback);

		glfwSetCharCallback(m_Window, WindowCharCallback);
	}

	void WindowsWindow::OnUpdate()
	{
		DC_PROFILE_FUNCTION();

		m_Context->SwapBuffers();
		glfwPollEvents();
	}

	void WindowsWindow::SetVSync(bool enable)
	{
		DC_PROFILE_FUNCTION();
		if (enable)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}
		m_Data.Vsync = enable;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.Vsync;
	}

	void WindowsWindow::WindowResizeCallback(GLFWwindow* window, int width, int height)
	{
		WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		data.width = width;
		data.height = height;

		WindowResizeEvent e(data.width, data.height);
		data.EventCallback(e);
	}

	void WindowsWindow::WindowCloseCallback(GLFWwindow* window)
	{
		WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		
		WindowCloseEvent e;
		data.EventCallback(e);
	}

	void WindowsWindow::WindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		switch (action)
		{
		case GLFW_PRESS:
		{
			KeyPressedEvent e(key, 0);
			data.EventCallback(e);
			break;
		}
		case GLFW_RELEASE:
		{
			KeyReleasedEvent e(key);
			data.EventCallback(e);
			break;
		}
		case GLFW_REPEAT:
		{
			KeyPressedEvent e(key, 1);
			data.EventCallback(e);
			break;
		}
		}
	}

	void WindowsWindow::WindowMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		switch (action)
		{
		case GLFW_PRESS:
		{
			MouseButtonPressedEvent e(button);
			data.EventCallback(e);
			break;
		}
		case GLFW_RELEASE:
		{
			MouseButtonReleasedEvent e(button);
			data.EventCallback(e);
			break;
		}
		}
	}

	void WindowsWindow::WindowMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		MouseScrolledEvent e((float)xoffset, (float)yoffset);
		data.EventCallback(e);
	}

	void WindowsWindow::WindowCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
	{
		WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		MouseMovedEvent e((float)xpos, (float)ypos);
		data.EventCallback(e);
	}
	void WindowsWindow::WindowCharCallback(GLFWwindow* window, unsigned int codepoint)
	{
		WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		KeyTypedEvent e(codepoint);
		data.EventCallback(e);
	}
}