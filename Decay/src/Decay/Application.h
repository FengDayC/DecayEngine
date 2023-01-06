#pragma once
#include "Core.h"
#include <memory>

namespace Decay
{
	class DECAY_API Application
	{
	public:
		Application();

		virtual ~Application();

		void Run();
	};

	std::shared_ptr<Application> CreateApplication();
}
