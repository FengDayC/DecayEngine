#pragma once
#include "entt\entt.hpp"
#include "Core.h"

namespace Decay
{
	class Entity;
	class Timestep;
	class DECAY_API Scene : public std::enable_shared_from_this<Scene>
	{
	public:
		Scene();
		~Scene();

	public:
		void Init();
		Entity AddEntity();

	public:
		void OnRuntimeUpdate(Timestep delta);
		void OnRenderUpdate(Timestep delta);

	public:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component)
		{

		}

	public:
		Entity GetMainCameraEntity();

		entt::registry& GetRegistry();

	private:
		entt::entity m_SceneEntity{ entt::null };
		entt::registry m_Registry;
	};
}