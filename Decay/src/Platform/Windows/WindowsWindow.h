#pragma once
#include<Decay\Core\Window.h>
#include<Decay/Renderer/GraphicsContext.h>

struct GLFWwindow;
class OpenGLContext;
namespace Decay
{
	class WindowsWindow : public Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		WindowsWindow(WindowProps props);
		virtual ~WindowsWindow();

		virtual void OnUpdate() override;

		virtual uint32_t GetWidth() const override { return m_Data.width; }
		virtual uint32_t GetHeight() const override { return m_Data.height; }

		virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;
		virtual void* GetNativeWindow() const override { return m_Window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;

		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int width, height;
			bool Vsync;
			EventCallbackFn EventCallback;


		};

		WindowData m_Data;

	//-----���ڻص�����----
	private:
		static void WindowResizeCallback(GLFWwindow* window, int width, int height);

		static void WindowCloseCallback(GLFWwindow* window);

		static void WindowKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		static void WindowMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

		static void WindowMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

		static void WindowCursorPosCallback(GLFWwindow* window, double xpos, double ypos);

		static void WindowCharCallback(GLFWwindow* window, unsigned int codepoint);
	};
}



