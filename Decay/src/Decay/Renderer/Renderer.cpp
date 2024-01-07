#include "dcpch.h"
#include "Renderer.h"
#include "Decay\Renderer\Shader.h"
#include "Decay\Renderer\Scene.h"
#include "Platform\OpenGL\OpenGLShader.h"
#include "Decay\Profile\Instrumentor.hpp"
#include "Renderer2D.h"
#include "Camera.h"
#include "Scene\Mesh.h"

namespace Decay
{
	void Renderer::Init()
	{
		DC_PROFILE_FUNCTION();
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::BeginScene(const Camera& camera)
	{
		s_camera = camera;
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::DrawMesh(const Mesh& mesh, const glm::mat4& transform)
	{
	}

	void Renderer::Submit(const S_PTR<Shader>& shader, const S_PTR<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMatrix4("decay_camera_viewMatrix", s_camera.GetViewMatrix());
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMatrix4("decay_camera_projectionMatrix", s_camera.GetProjectionMatrix());
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