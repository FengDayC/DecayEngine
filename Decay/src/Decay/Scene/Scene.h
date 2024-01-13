#include "entt\entt.hpp"
#include "Core.h"

namespace Decay
{
	class Entity;
	class DECAY_API Scene : public std::enable_shared_from_this<Scene>
	{
	public:
		Scene();
		~Scene();


	public:
		void OnRuntimeUpdate();
		void OnRenderUpdate();

	public:
		const Entity& GetMainCameraEntity() const;

	private:
		void Init();

	private:
		entt::entity m_SceneEntity{ entt::null };
		entt::registry m_Registry;
	};
}