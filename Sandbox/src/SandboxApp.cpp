#include <Decay.h>
#include <memory>
#include "ImGui\imgui.h"
#include "Platform\OpenGL\OpenGLShader.h"

using namespace Decay;

template<typename Fn>
class Timer
{
public:
	Timer(const std::string& name, Fn&& callbackFunc)
		: m_Name(name), m_Callback(callbackFunc), m_Stopped(false)
	{
		m_StartTimePoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
		{
			m_Stopped = true;
			Stop();
		}
	}

private:
	void Stop()
	{
		auto endTimePoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTimePoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimePoint).time_since_epoch().count();

		float duration = (end - start) * 0.001f;

		DC_CORE_INFO("Profile: {0} ms {1}", duration, m_Name.c_str());

		m_Callback({ m_Name,duration });
	}

private:
	std::string m_Name;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;
	bool m_Stopped;
	Fn m_Callback;
};

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
		m_VertexArray.reset(VertexArray::Create());

		std::vector<float> vertices
		{
			-.5f,-.5f,-.1f,.0,.0,
			-.5f,.5f,-.1f,.0,1.0,
			.5f,.5f,-.1f,1.0,1.0,
			.5f,-.5f,-.1f,1.0,.0
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices));

		{
			BufferLayout layout =
			{
				{ShaderDataType::Float3,"a_Pos"},
				{ShaderDataType::Float2,"a_UV"}
			};

			m_VertexBuffer->SetLayout(layout);
		}

		std::vector<uint32_t> indices{ 0,1,2,3,0,2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices));

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_ShaderLib.Load("assets/shaders/Texture.glsl");

		S_PTR<Camera> sceneCamera;
		sceneCamera.reset(new Camera());
		sceneCamera->SetPerspective(true);
		sceneCamera->SetFovy(90.0f);
		sceneCamera->SetRatio(16.0f / 9);
		sceneCamera->LookAt(glm::vec3(.0f, .0f, -1.0f), glm::vec3(.0f, .0f, .5f), glm::vec3(.0f, 1.0f, .0f));

		m_Scene.reset(new Scene(sceneCamera));

		m_Texture = Texture2D::Create("assets/texture/UV_Checker.png");
		std::dynamic_pointer_cast<OpenGLShader>(m_ShaderLib.Get("Texture"))->SetUniformInt("u_texture", 0);
	}

	~TestLayer()
	{

	}

	void OnAttach() override {}
	
	
	void OnDetach() override {}
	
	
	void OnUpdate(Timestep deltaTime) override 
	{
		//DC_INFO("DeltaTime = {0}", deltaTime->GetSeconds());

		Timer timer("Update", [&](ProfileResult result) { m_ProfileResults.push_back(result); });

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

		m_Texture->Bind(0);
		Renderer::Submit(m_ShaderLib.Get("Texture"), m_VertexArray);

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
	ShaderLibrary m_ShaderLib;
	S_PTR<VertexBuffer> m_VertexBuffer;
	S_PTR<IndexBuffer> m_IndexBuffer;
	S_PTR<VertexArray> m_VertexArray;
	S_PTR<Scene> m_Scene;
	S_PTR<Texture> m_Texture;

	std::vector<ProfileResult> m_ProfileResults;
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