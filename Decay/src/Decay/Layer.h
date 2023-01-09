#pragma once
#include "Core.h"
#include "Decay\Events\Event.h"

namespace Decay
{
	class DECAY_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");

		virtual ~Layer();

		virtual void OnAttach(){}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() { return m_DebugName; }

	protected:
		std::string m_DebugName;

	};
}
