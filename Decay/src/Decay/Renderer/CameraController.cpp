#include "dcpch.h"
#include "CameraController.h"
#include "Decay/Input/KeyCodes.h"
#include "Decay/Input/Input.h"

Decay::CameraController::CameraController(glm::vec3 position, glm::quat rotation, bool perspective, float ratio, float fovy,float size, float nearPlane, float farPlane)
{
	m_Camera = Camera(position, rotation, perspective, ratio, fovy, size, nearPlane, farPlane);
	m_OriginSize = size;
	m_ZoomLevel = 1.0f;
	m_Speed = 1.0f;
	m_OriginRatio = ratio;
}

void Decay::CameraController::OnUpdate(Timestep delta)
{
	if (m_Camera.IsPerspective())
	{
		if (Input::IsKeyPressed(DC_KEY_W))
		{
			m_Camera.Move(m_Camera.GetForward() * (float)delta);
		}
		if (Input::IsKeyPressed(DC_KEY_A))
		{
			m_Camera.Move(m_Camera.GetRight()* (float)-delta);
		}
		if (Input::IsKeyPressed(DC_KEY_S))
		{
			m_Camera.Move(m_Camera.GetForward() * (float)-delta);
		}
		if (Input::IsKeyPressed(DC_KEY_D))
		{
			m_Camera.Move(m_Camera.GetRight() * (float)delta);
		}
	}
	else
	{
		if (Input::IsKeyPressed(DC_KEY_W))
		{
			m_Camera.Move(m_Camera.GetUp() * (float)delta* m_Speed);
		}
		if (Input::IsKeyPressed(DC_KEY_A))
		{
			m_Camera.Move(m_Camera.GetRight() * (float)-delta* m_Speed);
		}
		if (Input::IsKeyPressed(DC_KEY_S))
		{
			m_Camera.Move(m_Camera.GetUp() * (float)-delta* m_Speed);
		}
		if (Input::IsKeyPressed(DC_KEY_D))
		{
			m_Camera.Move(m_Camera.GetRight() * (float)delta* m_Speed);
		}
	}
}

void Decay::CameraController::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseScrolledEvent>(DC_BIND_EVENT(CameraController::onMouseScrolled));
	dispatcher.Dispatch<WindowResizeEvent>(DC_BIND_EVENT(CameraController::onWindowResized));
}

bool Decay::CameraController::onMouseScrolled(MouseScrolledEvent& e)
{
	if (m_Camera.IsPerspective())
	{
		m_Camera.Move(m_Camera.GetForward() * e.GetYOffset() * 0.1f);
	}
	else
	{
		m_ZoomLevel-= e.GetYOffset() * 0.25f;
		m_ZoomLevel = glm::clamp(m_ZoomLevel, 0.25f, 100.0f);
		float size = m_OriginSize * m_ZoomLevel;
		m_Camera.SetSize(size);
	}
	m_Speed = m_ZoomLevel;
	return true;
}

bool Decay::CameraController::onWindowResized(WindowResizeEvent& e)
{
	m_Camera.SetRatio((float)e.GetWidth() / (float)e.GetHeight());
	return true;
}
