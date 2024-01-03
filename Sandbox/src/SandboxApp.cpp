#include <Decay.h>
#include <Decay\Core\EntryPoint.h>
#include <memory>
#include <ImGui\imgui.h>
#include "Platform\OpenGL\OpenGLShader.h"
#include "Sandbox2D.h"

using namespace Decay;

class TestLayer : public Layer
{
private:
	struct ProfileResult
	{
		std::string name;
		float duration;
	};
public:
	TestLayer() : Layer("TestLayer")
	{
		m_VertexArray = VertexArray::Create();

		std::vector<float> vertices
		{
			-.5f,-.5f,-.1f,.0,.0,
			-.5f,.5f,-.1f,.0,1.0,
			.5f,.5f,-.1f,1.0,1.0,
			.5f,-.5f,-.1f,1.0,.0
		};

		m_VertexBuffer = VertexBuffer::Create(vertices);

		{
			BufferLayout layout =
			{
				{ShaderDataType::Float3,"a_Pos"},
				{ShaderDataType::Float2,"a_UV"}
			};

			m_VertexBuffer->SetLayout(layout);
		}

		m_VertexArray->SetVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_ShaderLib.Load("assets/shaders/Texture.glsl");


		m_Texture = Texture2D::Create("assets/texture/UV_Checker.png");
		std::dynamic_pointer_cast<OpenGLShader>(m_ShaderLib.Get("Texture"))->UploadUniformInt("u_texture", 0);

		m_CameraController = CameraController::GetDefaultOrthographicController(16.0f / 9.0f);
		m_Scene.reset(new Scene(m_CameraController));
	}

	~TestLayer()
	{

	}

	void OnAttach() override {}
	
	
	void OnDetach() override {}
	
	
	void OnUpdate(Timestep deltaTime) override 
	{
		DC_PROFILE_FUNCTION();

		{
			DC_PROFILE_SCOPE("OnUpdate");
			m_Scene->GetSceneCameraController()->OnUpdate(deltaTime);
		}

		{
			DC_PROFILE_SCOPE("Renderer Prepare");
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();
		}

		{
			DC_PROFILE_SCOPE("Renderer Draw");
			Renderer::BeginScene(m_Scene);

			m_Texture->Bind(0);
			Renderer::Submit(m_ShaderLib.Get("Texture"), m_VertexArray);

			Renderer::EndScene();
		}
	}
	
	
	void OnImGuiRender() override 
	{
		ImGui::Begin("Test");
		ImGui::Text("Test Window");
		ImGui::End();
	}

	void OnEvent(Decay::Event& e) override 
	{
		m_Scene->GetSceneCameraController()->OnEvent(e);
	}

private:
	ShaderLibrary m_ShaderLib;
	S_PTR<VertexBuffer> m_VertexBuffer;
	S_PTR<IndexBuffer> m_IndexBuffer;
	S_PTR<VertexArray> m_VertexArray;
	S_PTR<Scene> m_Scene;
	S_PTR<Texture> m_Texture;

	S_PTR<CameraController> m_CameraController;

};

class Sandbox : public Decay::Application
{
public:
	Sandbox()
	{
		PushLayer(new Sandbox2D());
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