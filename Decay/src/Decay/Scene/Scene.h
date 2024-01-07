#include "entt\entt.hpp"

namespace Scene
{
	class Scene
	{
	public:
		Scene();
		~Scene();

	public:
		void OnRuntimeUpdate();
		void OnRenderUpdate();

	private:
		entt::registry m_Registry;
	};
}