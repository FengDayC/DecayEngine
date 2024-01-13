#include "dcpch.h"
#include "Entity.h"

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
		return m_Scene->m_registry.get<T>(m_EntityHandle);
	}

	template<typename T>
	const T& Entity::GetComponent() const
	{
		DC_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
		return m_Scene->m_registry.get<T>(m_EntityHandle);
	}

	template<typename T>
	bool Entity::HasComponent()
	{
		return m_Scene->m_registry.has<T>(m_EntityHandle);
	}

	template<typename T>
	void Entity::RemoveComponent()
	{
		DC_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
		m_Scene->m_registry.remove<T>(m_EntityHandle);
	}
}