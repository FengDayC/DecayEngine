#include "dcpch.h"
#include "Camera.h"
#include <glm\gtx\transform.hpp>
#include "Decay\Profile\Instrumentor.hpp"
#include <glm/gtx/euler_angles.hpp>

namespace Decay
{
	Camera::Camera()
	{
		m_Perspective = true;
		m_Ratio = 1.0f;
		m_Fovy = 45.0f;
		m_Size = 1.0f;
		m_Near = 0.1f;
		m_Far = 100.0f;
		RecalculateMatrix();
	}

	Camera::Camera(bool perspective, float ratio, float fovy,float size, float nearPlane, float farPlane)
		:m_Perspective(perspective), m_Ratio(ratio), m_Fovy(fovy), m_Size(size), m_Near(nearPlane), m_Far(farPlane)
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

	glm::mat4 Camera::CalculateMatrix(const glm::vec3& position, const glm::vec3& rotation) const
	{
		glm::mat4 viewMatrix = glm::translate(position) * glm::eulerAngleXYZ(rotation.x, rotation.y, rotation.z);
		return m_ProjectionMatrix * viewMatrix;
	}

	void Camera::RecalculateMatrix()
	{
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
