#include <dcpch.h>
#include "Scene.h"
#include <Profile/Instrumentor.hpp>
#include "Components.hpp"
#include "Entity.h"
#include "Renderer\Renderer.h"
#include "glm\glm.hpp"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace Decay
{
	Scene::Scene()
	{
		m_SceneEntity = m_Registry.create();
		Init();
	}

	Scene::~Scene()
	{
		m_Registry.destroy(m_SceneEntity);
		m_Registry.clear();
	}

	void Scene::Init()
	{
	}

	void Scene::OnRuntimeUpdate()
	{
		DC_PROFILE_FUNCTION

	}

	void Scene::OnRenderUpdate()
	{
		DC_PROFILE_FUNCTION
		Camera mainCamera = GetMainCameraEntity().GetComponent<CameraComponent>().OriginCamera;
		Renderer::BeginScene(mainCamera);
		auto view = m_Registry.view<MeshComponent, TransformComponent>();
		for(entt::entity entity : view)
		{
			auto [mesh, transform] = view.get<MeshComponent, TransformComponent>(entity);
			glm::mat4 transformMatrix = glm::translate(glm::mat4(1.0f), transform.Position)
				* glm::eulerAngleXYZ(glm::radians(transform.Rotation.x), glm::radians(transform.Rotation.y), glm::radians(transform.Rotation.z))
				* glm::scale(glm::mat4(1.0f), transform.Scale);
			Renderer::SubmitMesh(mesh.Mesh, transformMatrix);
		}
		Renderer::EndScene();
	}

	const Entity& Scene::GetMainCameraEntity() const
	{
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			const auto& camera = view.get<CameraComponent>(entity);
			if (camera.IsMainCamera)
			{
				return Entity(entity,shared_from_this());
			}
		}
		return {};
	}
}