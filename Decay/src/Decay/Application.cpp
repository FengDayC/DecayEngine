#include "dcpch.h"
#include "Application.h"
#include "Decay\Events\ApplicationEvent.h"
#include "Input.h"
#include "glad\glad.h"

namespace Decay
{
#define BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)

	U_PTR(Application) Application::s_Instance = nullptr;

	Application::Application() 
	{
		m_Window = U_PTR(Window)(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		DC_CORE_ASSERT(s_Instance, "Application is being recreate,but it should be singleton");
		s_Instance = U_PTR(Application)(this);
	}

	Application::~Application() 
	{
		DC_CORE_INFO("Application Instance Released!");
	}
	
	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			PAIR(float,float) pos = Input::GetMousePos();
			DC_CORE_INFO("Mouse Pos:({0},{1})", pos.first, pos.second);

			for (S_PTR(Layer) layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		//��������㼶ջ
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
			{
				break;
			}
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent e)
	{
		m_Running = false;
		DC_CORE_WARN("Window Close!");
		return true;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}
}