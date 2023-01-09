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


		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& e) override;

	//----Events----
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);


	private:
		float m_Time = 0.0f;
	};
}
