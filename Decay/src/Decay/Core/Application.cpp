#include "dcpch.h"
#include "Application.h"
#include "Decay\Input\Input.h"
#include "GLFW\glfw3.h"
#include "Decay\Renderer\Renderer.h"
#include "Decay\Profile\Instrumentor.hpp"

namespace Decay
{
#define BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)

	U_PTR<Application> Application::s_Instance = nullptr;

	Application::Application() 
	{
		DC_PROFILE_FUNCTION

		DC_CORE_ASSERT(!s_Instance, "Application already exists!");
		
		m_Window = U_PTR<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		DC_CORE_ASSERT(!s_Instance, "Application is being recreate,but it should be singleton");
		s_Instance = U_PTR<Application>(this);

		Renderer::Init();


		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_LastFrameTime = Timestep(glfwGetTime());
	}

	Application::~Application() 
	{
		DC_CORE_INFO("Application Instance Released!")
	}
	
	void Application::Run()
	{
		DC_PROFILE_FUNCTION

		while (m_Running)
		{
			DC_PROFILE_SCOPE("RunLoop");
			float nowTime = glfwGetTime();//Platform::GetTime()
			Timestep deltaTime = nowTime - m_LastFrameTime;
			m_LastFrameTime.SetSeconds(nowTime);

			if (!m_Minimize)
			{			
				{
					DC_PROFILE_SCOPE("LayerStack OnUpdate");
					
					for (S_PTR<Layer> layer : m_LayerStack)
					{
						layer->OnUpdate(deltaTime);
					}
				}
			}
			{
				DC_PROFILE_SCOPE("LayerStack ImguiUpdate");
				m_ImGuiLayer->Begin();
				for (S_PTR<Layer> layer : m_LayerStack)
				{
					layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}
			m_Window->OnUpdate();

		}
	}

	void Application::OnEvent(Event& e)
	{
		DC_PROFILE_FUNCTION
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

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
		DC_PROFILE_FUNCTION
		m_Running = false;
		DC_CORE_WARN("Window Close!");
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimize = true;
			return false;
		}

		m_Minimize = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

	void Application::PushLayer(Layer* layer)
	{
		DC_PROFILE_FUNCTION
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		DC_PROFILE_FUNCTION
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
}