#include "dcpch.h"
#include "ImGuiLayer.h"
#include"imgui.h"
#include "Platform\OpenGL\imgui_impl_opengl3.h"
#include "GLFW\glfw3.h"
#include "Decay\Application.h"
#include "glad\glad.h"

namespace Decay
{
	Decay::ImGuiLayer::ImGuiLayer():Layer("ImGuiLayer")
	{
	}

	Decay::ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsLight();

		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::GetApplication();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
	}

	void Decay::ImGuiLayer::OnUpdate()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		float time = (float)glfwGetTime();
		ImGuiIO& io = ImGui::GetIO();
		io.DeltaTime = time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Decay::ImGuiLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<MouseButtonPressedEvent>(DC_BIND_EVENT(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(DC_BIND_EVENT(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(DC_BIND_EVENT(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(DC_BIND_EVENT(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(DC_BIND_EVENT(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(DC_BIND_EVENT(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(DC_BIND_EVENT(ImGuiLayer::OnKeyTypedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(DC_BIND_EVENT(ImGuiLayer::OnWindowResizeEvent));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.MouseWheel += e.GetXOffset();
		io.MouseWheelH += e.GetYOffset();

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.KeysDown[e.GetKeyCode()] = true;
		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.KeysDown[e.GetKeyCode()] = false;
		
		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter(e.GetKeyCode());
		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0.f, 0.f, e.GetWidth(), e.GetHeight());

		return false;
	}
}


