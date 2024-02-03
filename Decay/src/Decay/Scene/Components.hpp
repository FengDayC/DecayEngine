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

		IDComponent() = default;
		IDComponent(const IDComponent& other) = default;

		operator UUID& () { return ID; }
		operator const UUID& () const { return ID; }
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

		TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = default;
	};

	struct MeshComponent
	{
		Mesh OriginMesh;

		MeshComponent() = default;
		MeshComponent(const MeshComponent& other) = default;

		operator Mesh& () { return OriginMesh; }
		operator const Mesh& () const { return OriginMesh; }
	};

	struct CameraComponent
	{
		Camera OriginCamera;
		bool IsMainCamera = true;

		CameraComponent() {}

		CameraComponent(const CameraComponent& other) = default;

		operator Camera& () { return OriginCamera; }
		operator const Camera& () const { return OriginCamera; }
	};
}