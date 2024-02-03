#pragma once
#include "Scene.h"
#include <entt\entt.hpp>

namespace Decay
{
	class Entity
	{
	friend class Scene;
	public:
		Entity() = default;
		Entity(const Entity& other) = default;
		Entity(Entity&& other) = default;
		Entity(entt::entity handle, S_PTR<Scene> scene)
			: m_EntityHandle(handle), m_Scene(scene) 
		{
		}
		Entity& operator=(const Entity& other) = default;
		Entity& operator=(Entity&& other) = default;
		virtual ~Entity() = default;

		template<typename T>
		T& GetComponent()
		{
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			DC_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		void RemoveComponent()
		{
			DC_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.all_of<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
		operator entt::entity() const { return m_EntityHandle; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }

		bool operator==(const Entity& other) const
		{
			return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}

	private:
		entt::entity m_EntityHandle{ entt::null };
		S_PTR<Scene> m_Scene;
	};
}