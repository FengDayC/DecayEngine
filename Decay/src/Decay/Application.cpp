#include "dcpch.h"
#include "Application.h"
#include "Decay\Events\ApplicationEvent.h"
#include "Input.h"

#include <glad\glad.h>

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


		m_VertexArray.reset(VertexArray::Create());

		std::vector<float> vertices
		{
			-.5f,-.5f,.0f,1.0f,.0f,1.0f,1.0f,
			.5f,-.5f,.0f ,1.0f,.0f,1.0f,1.0f,
			.0f,.5f,.0f  ,1.0f,.0f,1.0f,1.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices));

		{
			BufferLayout layout =
			{
				{ShaderDataType::Float3,"Position"},
				{ShaderDataType::Float4,"Color"}
			};

			m_VertexBuffer->SetLayout(layout);
		}

		std::vector<uint32_t> indices{ 0,1,2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices));

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSource = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Pos;
			layout(location = 1) in vec4 a_Color;
			out vec4 v_Color;

			void main()
			{
				gl_Position = vec4(a_Pos,1.0);
				v_Color = a_Color;
			}
			)";

		std::string fragmentSource = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
			)";

		m_Shader.reset(new Shader(vertexSource, fragmentSource));
	}

	Application::~Application() 
	{
		DC_CORE_INFO("Application Instance Released!");
	}
	
	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
			m_Shader->UnBind();

			for (S_PTR(Layer) layer : m_LayerStack)
			{
				layer->OnUpdate();
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