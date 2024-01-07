#pragma once
#include "Core.h"
#include "UUID.h"
#include <vector>
#include <glm\glm.hpp>
#include "Mesh.h"
#include "Renderer\Camera.h"

namespace Decay
{
	struct IDComponent
	{
		UUID ID;
	};

	struct RelationshipComponent
	{
		UUID Parent;
		std::vector<UUID> Children;
	};

	struct TransformComponent
	{
		glm::vec3 Position;
		glm::vec3 Rotation;
		glm::vec3 Scale;
	};

	struct MeshComponent
	{
		Mesh Mesh;
	};

	struct CameraComponent
	{
		Camera OriginCamera;
		bool IsMainCamera;
	};
}