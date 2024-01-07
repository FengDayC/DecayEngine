#pragma once
#include<glm\glm.hpp>
#include<glm\gtc\quaternion.hpp>

namespace Decay
{
	class DECAY_API Camera
	{
	public:
		Camera();
		Camera(glm::vec3 position = glm::vec3{ .0f,.0f,.0f }, glm::quat rotation = glm::quat{.0f,.0f,.0f,1.0f}, bool perspective = false, float ratio = 1.0f, float fovy = 90.0f, float size = 1.0f, float nearPlane = 0.01f, float farPlane = 1000.0f);
		
		inline void SetPosition(glm::vec3 position) { m_Position = position; RecalculateMatrix(); }
		inline void SetRotation(glm::quat rotation) { m_Rotation = rotation; RecalculateMatrix(); }
		inline void SetNear(float nearPlane) { m_Near = nearPlane; RecalculateMatrix(); }
		inline void SetFar(float farPlane) { m_Far = farPlane; RecalculateMatrix(); }
		inline void SetRatio(float ratio) { m_Ratio = ratio; RecalculateMatrix(); }
		inline void SetPerspective(bool perspective) { m_Perspective = perspective; RecalculateMatrix(); }
		
		void SetFovy(float fovy);
		void SetSize(float size);

	public:
		void Move(glm::vec3 delta);

		void LookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up);

	public:
		inline glm::vec3 GetPosition() const { return m_Position; }
		inline glm::quat GetRotation() const { return m_Rotation; }
		inline glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
		inline glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }

		inline glm::vec3 GetForward() const { return glm::normalize(glm::vec3{ m_ViewMatrix[0][2],m_ViewMatrix[1][2],m_ViewMatrix[2][2] }); }
		inline glm::vec3 GetRight() const { return glm::normalize(glm::vec3{ m_ViewMatrix[0][0],m_ViewMatrix[1][0],m_ViewMatrix[2][0] }); }
		inline glm::vec3 GetUp() const { return glm::normalize(glm::vec3{ m_ViewMatrix[0][1],m_ViewMatrix[1][1],m_ViewMatrix[2][1] }); }
		inline float GetSize() const { return m_Size; }

		inline bool IsPerspective() const { return m_Perspective; }
	private:
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		
		bool m_Perspective;
		glm::vec3 m_Position;
		glm::quat m_Rotation;
		float m_Near;
		float m_Far;
		float m_Ratio;
		float m_Fovy;
		float m_Size;
	
	private:
		void RecalculateMatrix();
	};
}
