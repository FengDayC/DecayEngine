#pragma once
#include "Core.h"
#include "Window.h"
#include "Events\Event.h"
#include "Events\ApplicationEvent.h"

namespace Decay
{
	class DECAY_API Application
	{
	public:
		Application();

		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

	private:
		std::unique_ptr<Window> m_Window;

		bool m_Running = true;

		bool OnWindowClose(WindowCloseEvent e);
	};

	std::shared_ptr<Application> CreateApplication();
}
