#include "dcpch.h"
#include "Camera.h"
#include <glm\gtx\transform.hpp>
#include "Decay\Profile\Instrumentor.hpp"

namespace Decay
{
	Camera::Camera()
	{
		m_Position = glm::vec3(0.0f);
		m_Rotation = glm::quat(glm::vec3(0.0f));
		m_Perspective = true;
		m_Ratio = 1.0f;
		m_Fovy = 45.0f;
		m_Size = 1.0f;
		m_Near = 0.1f;
		m_Far = 100.0f;
		RecalculateMatrix();
	}

	Camera::Camera(glm::vec3 position, glm::quat rotation, bool perspective, float ratio, float fovy,float size, float nearPlane, float farPlane)
		:m_Position(position), m_Rotation(rotation), m_Perspective(perspective), m_Ratio(ratio), m_Fovy(fovy), m_Size(size), m_Near(nearPlane), m_Far(farPlane)
	{
		RecalculateMatrix();
	}

	/// <summary>
	/// Fovy
	/// </summary>
	/// <param name="fovy">use degree</param>
	void Camera::SetFovy(float fovy)
	{
		DC_PROFILE_FUNCTION
		if (!m_Perspective)
		{
			DC_CORE_WARN("Trying to set fov for a orthographic camera");
		}
		m_Fovy = fovy;
		RecalculateMatrix();
	}

	void Camera::SetSize(float size)
	{
		DC_PROFILE_FUNCTION
		if (m_Perspective)
		{
			DC_CORE_WARN("Trying to set size for a perspective camera");
		}
		m_Size = size;
		RecalculateMatrix();
	}

	void Camera::Move(glm::vec3 delta)
	{
		DC_PROFILE_FUNCTION
		m_Position += delta;
		RecalculateMatrix();
	}

	void Camera::LookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
	{
		DC_PROFILE_FUNCTION
		m_Position = center;
		glm::vec3 backVec = glm::normalize(center - eye);
		up = glm::normalize(up);
		glm::vec3 rightVec = glm::cross(up, backVec);
		glm::mat4 rotationMatrix = glm::mat4(glm::mat3(rightVec, up, backVec));
		m_Rotation = glm::quat_cast(rotationMatrix);
		RecalculateMatrix();
	}

	void Camera::RecalculateMatrix()
	{
		glm::mat4 orientation = glm::mat4_cast(m_Rotation);
		m_ViewMatrix = glm::inverse(glm::translate(glm::mat4(1.0f), m_Position) * orientation);

		if (m_Perspective)
		{
			m_ProjectionMatrix = glm::perspective(m_Fovy*glm::pi<float>()/180.0f, m_Ratio, m_Near, m_Far);
		}
		else
		{
			float hlfWidth = m_Size / 2.0f * m_Ratio;
			float hlfHeight = m_Size / 2.0f;
			m_ProjectionMatrix = glm::ortho(-hlfWidth, hlfWidth, -hlfHeight, hlfHeight);
		}
	}

}
