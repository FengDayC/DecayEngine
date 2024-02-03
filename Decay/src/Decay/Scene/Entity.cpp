#include "dcpch.h"
#include "Entity.h"
#include "Scene.h"
#include <entt\entt.hpp>

namespace Decay
{
	template<typename T, typename... Args>
	T& Entity::AddComponent(Args&&... args)
	{
		DC_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
		T& component = m_Scene->m_registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		m_Scene->OnComponentAdded<T>(*this, component);
		return component;
	}

	template<typename T>
	T& Entity::GetComponent()
	{
		DC_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
		return m_Scene.lock()->m_Registry.get<T>(m_EntityHandle);
	}

	template<typename T>
	bool Entity::HasComponent()
	{
		return m_Scene.lock()->m_Registry.all_of<T>(m_EntityHandle);
	}

	template<typename T>
	void Entity::RemoveComponent()
	{
		DC_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
		m_Scene.lock()->m_Registry.remove<T>(m_EntityHandle);
	}
}