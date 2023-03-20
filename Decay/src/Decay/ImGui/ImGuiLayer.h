#pragma once
#include "Decay\Core\Layer.h"
#include "Decay\Core\Events\KeyEvent.h"
#include "Decay\Core\Events\MouseEvent.h"
#include "Decay\Core\Events\ApplicationEvent.h"

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
