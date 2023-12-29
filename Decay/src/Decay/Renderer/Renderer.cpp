#include "dcpch.h"
#include "Renderer.h"
#include "Decay\Renderer\Shader.h"
#include "Decay\Renderer\Scene.h"
#include "Platform\OpenGL\OpenGLShader.h"
#include "Decay\Profile\Instrumentor.hpp"
#include "Renderer2D.h"

namespace Decay
{
	S_PTR<Scene>& Renderer::s_Scene = std::make_shared<Scene>();

	void Renderer::Init()
	{
		DC_PROFILE_FUNCTION();
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::BeginScene(const S_PTR<Scene>& scene)
	{
		s_Scene = scene;
	}

	void Renderer::EndScene()
	{
		s_Scene = nullptr;
	}

	void Renderer::Submit(const S_PTR<Shader>& shader, const S_PTR<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMatrix4("decay_camera_viewMatrix", s_Scene->GetSceneCameraController()->GetCamera().GetViewMatrix());
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMatrix4("decay_camera_projectionMatrix", s_Scene->GetSceneCameraController()->GetCamera().GetProjectionMatrix());
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMatrix4("decay_model_transform", transform);
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
		vertexArray->UnBind();

		shader->UnBind();
	}
	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}
}