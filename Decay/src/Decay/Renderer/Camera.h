#pragma once
#include<glm\glm.hpp>
#include<glm\gtc\quaternion.hpp>

namespace Decay
{
	class DECAY_API Camera
	{
	public:
		Camera();
		Camera(bool perspective, float ratio = 1.0f, float fovy = 90.0f, float size = 1.0f, float nearPlane = 0.01f, float farPlane = 1000.0f);
		
		inline void SetNear(float nearPlane) { m_Near = nearPlane; RecalculateMatrix(); }
		inline void SetFar(float farPlane) { m_Far = farPlane; RecalculateMatrix(); }
		inline void SetRatio(float ratio) { m_Ratio = ratio; RecalculateMatrix(); }
		inline void SetPerspective(bool perspective) { m_Perspective = perspective; RecalculateMatrix(); }
		
		void SetFovy(float fovy);
		void SetSize(float size);

		glm::mat4 CalculateMatrix(const glm::vec3& position, const glm::vec3& rotation) const;

	public:
		inline glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }

		inline float GetSize() const { return m_Size; }

		inline bool IsPerspective() const { return m_Perspective; }
	private:
		glm::mat4 m_ProjectionMatrix;
		
		bool m_Perspective;
		float m_Near;
		float m_Far;
		float m_Ratio;
		float m_Fovy;
		float m_Size;
	
	private:
		void RecalculateMatrix();
	};
}
