#pragma once
#include "Core.h"
#include "UUID.h"
#include "entt\entt.hpp"
#include "Components.hpp"

namespace Decay
{
	class Scene;
	class DECAY_API Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, S_PTR<const Decay::Scene> scene)
			: m_EntityHandle(handle), m_Scene(scene) {}

		virtual ~Entity() = default;

		entt::entity GetEntityHandle() const { return m_EntityHandle; }

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args);

		template<typename T>
		const T& GetComponent() const;

		template<typename T>
		T& GetComponent();

		template<typename T>
		bool HasComponent();

		template<typename T>
		void RemoveComponent();

		inline operator bool() const { return m_EntityHandle != entt::null; }
		inline operator uint64_t() const { return (uint64_t)m_EntityHandle; }
		inline UUID GetUUID() const { return GetComponent<IDComponent>().ID; }

	private:
		entt::entity m_EntityHandle{ entt::null };
		W_PTR<const Scene> m_Scene;
	};
}