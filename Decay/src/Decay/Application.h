#pragma once
#include "Core.h"
#include "Window.h"
#include "Events\Event.h"
#include "Events\ApplicationEvent.h"
#include "Layer.h"
#include "LayerStack.h"
#include <Decay\Log.h>
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
		U_PTR(Window) m_Window;

		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;

		LayerStack m_LayerStack;

		bool OnWindowClose(WindowCloseEvent e);

		unsigned int m_VAO, m_VBO, m_VEO;

	private:
		static std::unique_ptr<Application> s_Instance;
	};

	void CreateApplication();
}
