#pragma once
#include <glm\glm.hpp>
#include "Decay\Renderer\Camera.h"

namespace Decay
{

	class DECAY_API Scene
	{
	public:

	public: 
		Scene() {}

		Scene(const S_PTR<Camera>& camera);

		inline S_PTR<Camera> GetSceneCamera() const { return m_SceneCamera; }

	private:
		S_PTR<Camera> m_SceneCamera;
	};

}