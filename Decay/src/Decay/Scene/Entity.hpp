#pragma once
#include <dcpch.h>
#include "Scene.h"
#include <entt\entt.hpp>

namespace Decay
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(const Entity& other) = default;
		Entity(Entity&& other) = default;
		Entity(const entt::entity& handle, W_PTR<Scene> scene)
			: m_EntityHandle(handle), m_Scene(scene)
		{
		}

		Entity& operator=(const Entity& other) = default;
		Entity& operator=(Entity&& other) = default;
		virtual ~Entity() = default;

		template<typename T>
		T& GetComponent()
		{
			DC_CORE_ASSERT(HasComponent<T>(), "Entity doesn't has component!");
			auto sp = m_Scene.lock();
			return sp->GetRegistry().get<T>(m_EntityHandle);
		}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			DC_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			auto sp = m_Scene.lock();
			return sp->GetRegistry().emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		void RemoveComponent()
		{
			DC_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			auto sp = m_Scene.lock();
			sp->GetRegistry().remove<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			auto sp = m_Scene.lock();
			return sp->GetRegistry().all_of<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
		operator entt::entity() const { return m_EntityHandle; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }

		bool operator==(const Entity& other) const
		{
			return m_EntityHandle == other.m_EntityHandle;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}

	private:
		entt::entity m_EntityHandle{ entt::null };
		W_PTR<Scene> m_Scene;
	};
}