#pragma once
#include "Decay\Core.h"
#include "Window.h"
#include "Events\Event.h"
#include "Events\ApplicationEvent.h"
#include "Layer.h"
#include "LayerStack.h"
#include "Decay\Logger\Logger.h"
#include "Decay\ImGui\ImGuiLayer.h"

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
		U_PTR<Window> m_Window;

		ImGuiLayer* m_ImGuiLayer;

		LayerStack m_LayerStack;

		Timestep m_LastFrameTime;

		bool m_Running = true;

		bool m_Minimize = false;

		bool OnWindowClose(WindowCloseEvent e);
		
		bool OnWindowResize(WindowResizeEvent e);

	private:
		static U_PTR<Application> s_Instance;
	};

	void CreateApplication();
}
