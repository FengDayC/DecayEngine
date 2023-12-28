#pragma once
#include <glm\glm.hpp>
#include "Decay\Renderer\Camera.h"
#include "Decay\Renderer\CameraController.h"

namespace Decay
{

	class DECAY_API Scene
	{
	public:

	public: 
		Scene() {}

		Scene(const S_PTR<CameraController>& cameraController);

		inline S_PTR<CameraController> GetSceneCameraController() const { return m_SceneCameraController; }

	private:
		S_PTR<CameraController> m_SceneCameraController;
	};

}