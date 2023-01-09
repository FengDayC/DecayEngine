#pragma once
#include "Decay\Layer.h"
#include "Decay\Events\KeyEvent.h"
#include "Decay\Events\MouseEvent.h"
#include "Decay\Events\ApplicationEvent.h"

namespace Decay
{
	class DECAY_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();


		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender();

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}
