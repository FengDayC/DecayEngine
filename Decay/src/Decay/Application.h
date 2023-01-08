#pragma once
#include "Core.h"
#include "Window.h"
#include "Events\Event.h"
#include "Events\ApplicationEvent.h"
#include "Layer.h"
#include "LayerStack.h"

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

	private:
		std::unique_ptr<Window> m_Window;

		bool m_Running = true;

		LayerStack m_LayerStack;

		bool OnWindowClose(WindowCloseEvent e);
	};

	std::shared_ptr<Application> CreateApplication();
}
