#pragma once
#include "Decay\Core.h"
#include "Decay\Core\Events\Event.h"
#include "Decay\Core\Timestep.h"

namespace Decay
{
	class DECAY_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");

		virtual ~Layer();

		virtual void OnAttach(){}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep deltaTime) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() { return m_DebugName; }

	protected:
		std::string m_DebugName;

	};
}
