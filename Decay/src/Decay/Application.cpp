#include "dcpch.h"
#include "Application.h"
#include "Decay\Events\ApplicationEvent.h"
#include "Decay\Renderer\Renderer.h"
#include "Decay\Renderer\Camera.h"
#include "Input.h"

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
			-.5f,-.5f,-.1f,.1f,.2f,.8f,1.0f,
			.5f,-.5f,-.1f ,.1f,.7f,.3f,1.0f,
			.0f,.5f,-.1f  ,1.0f,.2f,.2f,1.0f
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
			uniform mat4 decay_camera_viewMatrix;
			uniform mat4 decay_camera_projectionMatrix;

			void main()
			{
				gl_Position = decay_camera_projectionMatrix * decay_camera_viewMatrix * vec4(a_Pos,1.0);
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

		S_PTR(Camera) sceneCamera;
		sceneCamera.reset(new Camera());
		sceneCamera->SetPerspective(true);
		sceneCamera->SetFovy(90.0f);
		sceneCamera->SetRatio(16.0f / 9);
		sceneCamera->LookAt(glm::vec3(.0f, .0f, -1.0f), glm::vec3(.0f, .0f, .5f), glm::vec3(.0f, 1.0f, .0f));

		m_Scene.reset(new Scene(sceneCamera));

		NowTime = .0f;
	}

	Application::~Application() 
	{
		DC_CORE_INFO("Application Instance Released!");
	}
	
	void Application::Run()
	{
		NowTime += (1.0f / 144);
		while (m_Running)
		{
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			m_Scene->GetSceneCamera()->Move(glm::vec3(.0f, .0f, NowTime));

			Renderer::BeginScene(m_Scene);

			Renderer::Submit(m_Shader,m_VertexArray);

			Renderer::EndScene();

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