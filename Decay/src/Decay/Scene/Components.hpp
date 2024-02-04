#pragma once
#include "Core.h"
#include "UUID.h"
#include <vector>
#include <glm\glm.hpp>
#include "Mesh.h"
#include "Renderer\Camera.h"
#include <glm/gtx/euler_angles.hpp>

namespace Decay
{
	struct IDComponent
	{
		UUID ID;

		IDComponent(UUID id)
			: ID(id)
		{
		}

		IDComponent() = default;
		IDComponent(const IDComponent& other) = default;

		operator UUID& () { return ID; }
		operator const UUID& () const { return ID; }
	};

	struct TransformComponent
	{
		glm::vec3 Position;
		glm::vec3 Rotation; //Degree
		glm::vec3 Scale;

		TransformComponent(glm::vec3 position, glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f))
			: Position(position), Rotation(rotation), Scale(scale)
		{
		}
		TransformComponent()
		{
			Position = glm::vec3(0.0f);
			Rotation = glm::vec3(0.0f);
			Scale = glm::vec3(1.0f);
		}
		TransformComponent(const TransformComponent& other) = default;

		glm::mat4 GetTransformMatrix()
		{
			return glm::translate(glm::mat4(1.0f), Position)
				* glm::eulerAngleXYZ(glm::radians(Rotation.x), glm::radians(Rotation.y), glm::radians(Rotation.z))
				* glm::scale(glm::mat4(1.0f), Scale);
		}
	};

	struct MeshComponent
	{
		Mesh OriginMesh;

		MeshComponent(Mesh mesh)
			: OriginMesh(mesh)
		{
		}
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

		CameraComponent(Camera camera, bool isMain)
			: OriginCamera(camera), IsMainCamera(isMain)
		{
		}

		CameraComponent(const CameraComponent& other) = default;

		operator Camera& () { return OriginCamera; }
		operator const Camera& () const { return OriginCamera; }
	};
}