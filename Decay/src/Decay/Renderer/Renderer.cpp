#include "dcpch.h"
#include "Renderer.h"
#include "Decay\Renderer\Shader.h"
#include "Decay\Renderer\Scene.h"

namespace Decay
{
	S_PTR(Scene)& Renderer::s_Scene = std::make_shared<Scene>();

	void Renderer::BeginScene(const S_PTR(Scene)& scene)
	{
		s_Scene = scene;
	}

	void Renderer::EndScene()
	{
		s_Scene = nullptr;
	}

	void Renderer::Submit(const S_PTR(Shader)& shader, const S_PTR(VertexArray)& vertexArray)
	{
		shader->Bind();
		shader->SetUniformMatrix4("decay_camera_viewMatrix", s_Scene->GetSceneCamera()->GetViewMatrix());
		shader->SetUniformMatrix4("decay_camera_projectionMatrix", s_Scene->GetSceneCamera()->GetProjectionMatrix());
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
		vertexArray->UnBind();

		shader->UnBind();
	}
}