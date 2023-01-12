#include <Decay.h>
#include <memory>
#include "ImGui\imgui.h"

using namespace Decay;

class TestLayer : public Layer
{
public:
	TestLayer() : Layer("TestLayer")
	{
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
			uniform mat4 decay_model_transform;

			void main()
			{
				gl_Position = decay_camera_projectionMatrix * decay_camera_viewMatrix * decay_model_transform * vec4(a_Pos,1.0);
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
	}

	~TestLayer()
	{

	}

	void OnAttach() override {}
	
	
	void OnDetach() override {}
	
	
	void OnUpdate(Timestep deltaTime) override 
	{
		//DC_INFO("DeltaTime = {0}", deltaTime->GetSeconds());

		if (Input::IsKeyPressed(DC_KEY_W))
		{
			m_Scene->GetSceneCamera()->Move(glm::vec3(.0, .1 * deltaTime, .0));
		}
		if (Input::IsKeyPressed(DC_KEY_A))
		{
			m_Scene->GetSceneCamera()->Move(glm::vec3(-0.1 * deltaTime, .0, .0));
		}
		if (Input::IsKeyPressed(DC_KEY_S))
		{
			m_Scene->GetSceneCamera()->Move(glm::vec3(.0, -.1 * deltaTime, .0));
		}
		if (Input::IsKeyPressed(DC_KEY_D))
		{
			m_Scene->GetSceneCamera()->Move(glm::vec3(0.1 * deltaTime, .0, .0));
		}

		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RenderCommand::Clear();

		Renderer::BeginScene(m_Scene);

		Renderer::Submit(m_Shader, m_VertexArray);

		Renderer::EndScene();
	}
	
	
	void OnImGuiRender() override 
	{
		ImGui::Begin("Test");
		ImGui::Text("Test Window");
		ImGui::End();
	}

	void OnEvent(Decay::Event& e) override {}

private:
	S_PTR(Shader) m_Shader;
	S_PTR(VertexBuffer) m_VertexBuffer;
	S_PTR(IndexBuffer) m_IndexBuffer;
	S_PTR(VertexArray) m_VertexArray;
	S_PTR(Scene) m_Scene;
};

class Sandbox : public Decay::Application
{
public:
	Sandbox()
	{
		PushLayer(new TestLayer());
	}

	~Sandbox() override
	{
		DC_INFO("Sandbox Release!");
	}
};

void Decay::CreateApplication()
{
	new Sandbox();
}