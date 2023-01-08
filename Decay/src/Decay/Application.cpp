#include "dcpch.h"
#include "Application.h"
#include "Decay\Events\ApplicationEvent.h"
#include "dcpch.h"
#include "GLFW\glfw3.h"

namespace Decay
{
#define BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)

	Application::Application() 
	{
		m_Window = U_PTR(Window)(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application() {}
	
	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
	}

	bool Application::OnWindowClose(WindowCloseEvent e)
	{
		m_Running = false;
		DC_CORE_WARN("Window Close!");
		return true;
	}
}