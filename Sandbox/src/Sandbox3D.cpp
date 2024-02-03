#include "Sandbox3D.h"
using namespace Decay;

void Sandbox3D::OnAttach()
{
	mainScene = CreateS_PTR<Scene>();
	mainScene->Init();
	Entity buildingEntity = mainScene->AddEntity();
	S_PTR<MeshSource> sponzaSrc = CreateS_PTR<MeshSource>("Assets/Models/sponza3/source/glTF/Sponza.gltf");
	buildingEntity.AddComponent<MeshComponent>(Mesh(sponzaSrc));
}

void Sandbox3D::OnDetach()
{
}

void Sandbox3D::OnUpdate(Decay::Timestep deltaTime)
{
	{
		DC_PROFILE_SCOPE("Main scene runtime update")
		mainScene->OnRuntimeUpdate(deltaTime);
	}
	{
		DC_PROFILE_SCOPE("Main scene render update")
		mainScene->OnRenderUpdate(deltaTime);
	}
}

void Sandbox3D::OnImGuiRender()
{
}

void Sandbox3D::OnEvent(Decay::Event& e)
{
}
