#include "dcpch.h"
#include "Application.h"
#include "Input.h"
#include "GLFW\glfw3.h"

namespace Decay
{
#define BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)

	U_PTR(Application) Application::s_Instance = nullptr;

	Application::Application() 
	{
		m_Window = U_PTR(Window)(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		DC_CORE_ASSERT(!s_Instance, "Application is being recreate,but it should be singleton");
		s_Instance = U_PTR(Application)(this);

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_LastFrameTime.reset(new Timestep(glfwGetTime()));
	}

	Application::~Application() 
	{
		DC_CORE_INFO("Application Instance Released!");
	}
	
	void Application::Run()
	{
		while (m_Running)
		{
			float nowTime = glfwGetTime();
			Timestep deltaTime = nowTime - *m_LastFrameTime;
			m_LastFrameTime->SetSeconds(nowTime);

			for (S_PTR(Layer) layer : m_LayerStack)
			{
				layer->OnUpdate(deltaTime);
			}

			m_ImGuiLayer->Begin();
			for (S_PTR(Layer) layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		//·´Ðò±éÀú²ã¼¶Õ»
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
		layer->OnAttach();
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		overlay->OnAttach();
		m_LayerStack.PushOverlay(overlay);
	}
}