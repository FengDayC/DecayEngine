#pragma once
#include "Core.h"
#include "Window.h"
#include "Events\Event.h"
#include "Events\ApplicationEvent.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Decay\Log.h"
#include "Decay\ImGui\ImGuiLayer.h"
#include "Decay\Renderer\Shader.h"
#include "Decay\Renderer\Buffer.h"
#include "Decay\Renderer\VertexArray.h"

namespace Decay
{
	class DECAY_API Application
	{
	public:
		Application();

		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);

		void PushOverlay(Layer* overlay);

		inline static Application& GetApplication() { return *s_Instance; }

		inline static void ReleaseApplication() { s_Instance = nullptr; }

		inline Window& GetWindow() const { return *m_Window; }

	private:
		U_PTR(Window) m_Window;

		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;

		LayerStack m_LayerStack;

		bool OnWindowClose(WindowCloseEvent e);

		S_PTR(Shader) m_Shader;
		S_PTR(VertexBuffer) m_VertexBuffer;
		S_PTR(IndexBuffer) m_IndexBuffer;
		S_PTR(VertexArray) m_VertexArray;

	private:
		static U_PTR(Application) s_Instance;
	};

	void CreateApplication();
}
