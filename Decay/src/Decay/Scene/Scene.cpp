#include <dcpch.h>
#include "Scene.h"
#include <Profile/Instrumentor.hpp>
#include "Components.hpp"
#include "Entity.hpp"
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
	}

	Scene::~Scene()
	{
		m_Registry.destroy(m_SceneEntity);
		m_Registry.clear();
	}

	Entity Scene::AddEntity()
	{
		entt::entity entityHandle = m_Registry.create();
		auto wp = weak_from_this();
		Entity entity(entityHandle, wp);
		entity.AddComponent<IDComponent>(UUID::GetNewUUID());
		return entity;
	}

	void Scene::Init()
	{
		m_SceneEntity = m_Registry.create();
		m_Registry.emplace<IDComponent>(m_SceneEntity, UUID::GetNewUUID());
		Entity cameraEntity = AddEntity();
		cameraEntity.AddComponent<CameraComponent>(Camera(), true);
		cameraEntity.AddComponent<TransformComponent>();
	}

	void Scene::OnRuntimeUpdate(Timestep delta)
	{
		DC_PROFILE_FUNCTION

	}

	void Scene::OnRenderUpdate(Timestep delta)
	{
		DC_PROFILE_FUNCTION
		Renderer::BeginScene(shared_from_this());
		auto view = m_Registry.view<MeshComponent, TransformComponent>();
		for(entt::entity entity : view)
		{
			std::tuple<MeshComponent, TransformComponent> t = view.get<MeshComponent, TransformComponent>(entity);
			TransformComponent transform = std::get<TransformComponent>(t);
			MeshComponent mesh = std::get<MeshComponent>(t);
			glm::mat4 transformMatrix = transform.GetTransformMatrix();
			Renderer::SubmitMesh(mesh.OriginMesh, transformMatrix);
		}
		Renderer::EndScene();
	}

	Entity Scene::GetMainCameraEntity()
	{
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			CameraComponent camera = view.get<CameraComponent>(entity);
			if (camera.IsMainCamera)
			{
				return Entity(entity, shared_from_this());
			}
		}
		return {};
	}

	entt::registry& Scene::GetRegistry()
	{
		return m_Registry;
	}
}