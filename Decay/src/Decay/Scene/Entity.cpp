#include "dcpch.h"
#include "Entity.h"

namespace Decay
{
	template<typename T, typename... Args>
	T& Entity::AddComponent(Args&&... args)
	{
		DC_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
		T& component = m_scene->m_registry.emplace<T>(m_entityHandle, std::forward<Args>(args)...);
		m_scene->OnComponentAdded<T>(*this, component);
		return component;
	}

	template<typename T>
	T& Entity::GetComponent()
	{
		DC_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
		return m_scene->m_registry.get<T>(m_entityHandle);
	}

	template<typename T>
	const T& Entity::GetComponent() const
	{
		DC_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
		return m_scene->m_registry.get<T>(m_entityHandle);
	}

	template<typename T>
	bool Entity::HasComponent()
	{
		return m_scene->m_registry.has<T>(m_entityHandle);
	}

	template<typename T>
	void Entity::RemoveComponent()
	{
		DC_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
		m_scene->m_registry.remove<T>(m_entityHandle);
	}
}