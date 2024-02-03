#include <dcpch.h>
#include "Scene.h"
#include <Profile/Instrumentor.hpp>
#include "Components.hpp"
#include "Entity.h"
#include "Renderer\Renderer.h"
#include "Core\Timestep.h"
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

	Entity Scene::AddEntity()
	{
		Entity entity(m_Registry.create(), shared_from_this());
		entity.AddComponent<IDComponent>(UUID::GetNewUUID());	
		entity.AddComponent<RelationshipComponent>(m_Registry.get<IDComponent>(m_SceneEntity).ID);
		return entity;
	}

	void Scene::Init()
	{
		m_SceneEntity = m_Registry.create();
		m_Registry.emplace<IDComponent>(m_SceneEntity, UUID::GetNewUUID());
	}

	void Scene::OnRuntimeUpdate(Timestep delta)
	{
		DC_PROFILE_FUNCTION

	}

	void Scene::OnRenderUpdate(Timestep delta)
	{
		DC_PROFILE_FUNCTION
		Camera mainCamera = GetMainCameraEntity().GetComponent<CameraComponent>().OriginCamera;
		Renderer::BeginScene(shared_from_this());
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

	Entity Scene::GetMainCameraEntity()
	{
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			const auto& camera = view.get<CameraComponent>(entity);
			if (camera.IsMainCamera)
			{
				return Entity(entity, shared_from_this());
			}
		}
		return {};
	}

	template<typename T>
	void Scene::OnComponentAdded(Entity* entity, T& component)
	{

	}
}