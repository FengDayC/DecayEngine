#pragma once
#include "Decay\Renderer\Camera.h"
#include "Decay\Core\Timestep.h"
#include "Decay\Core\Events\Event.h"
#include <Decay/Core/Events/MouseEvent.h>
#include <Decay/Core/Events/KeyEvent.h>
#include <Decay/Core/Events/ApplicationEvent.h>

namespace Decay
{
	class DECAY_API CameraController
	{
	public:
		CameraController(glm::vec3 position, glm::quat rotation, bool perspective, float ratio, float fovy,float size, float nearPlane, float farPlane);

		void OnUpdate(Timestep delta);

		void OnEvent(Event& e);

	public:
	
		bool onMouseScrolled(MouseScrolledEvent& e);

		bool onWindowResized(WindowResizeEvent& e);

	public:
		inline static S_PTR<CameraController> GetDefaultOrthographicController(float aspectRatio)
		{
			return std::make_shared<CameraController>(glm::vec3(0.0f), glm::quat(glm::vec3(0.0f)), false, aspectRatio, 0.0f, 1.0f, -1.0f, 1.0f);
		}

		inline static S_PTR<CameraController> GetDefaultPerspectiveController(float aspectRatio)
		{
			return std::make_shared<CameraController>(glm::vec3(0.0f), glm::quat(glm::vec3(0.0f)), true, aspectRatio, glm::radians(45.0f), 0.0f, 0.1f, 100.0f);
		}

	public:

		inline Camera& GetCamera() { return m_Camera; }

		inline const Camera& GetCamera() const { return m_Camera; }

	private:
		Camera m_Camera;

		float m_ZoomLevel = 1.0f;

		float m_OriginSize = 1.0f;

		float m_OriginRatio = 16.0f / 9.0f;

		float m_Speed = 1.0f;
	};
}
