#include "dcpch.h"
#include "Decay\Renderer\Shader.h"
#include "Decay\Renderer\Renderer.h"
#include "Platform\OpenGL\OpenGLShader.h"

namespace Decay
{
	S_PTR<Shader> Shader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
	{
		RendererAPI::API api = Renderer::GetAPI();
		DC_CORE_ASSERT((uint32_t)api, "No Renderer API");
		switch (api)
		{
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(name, vertexSource, fragmentSource);
		}
		return nullptr;
	}	
	
	S_PTR<Shader> Shader::Create(const std::string& path)
	{
		RendererAPI::API api = Renderer::GetAPI();
		DC_CORE_ASSERT((uint32_t)api, "No Renderer API");
		switch (api)
		{
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(path);
		}
		return nullptr;
	}

	void ShaderLibrary::Add(const S_PTR<Shader>& shader)
	{
		auto name = shader->GetName();
		DC_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader readd!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const std::string& name, const S_PTR<Shader>& shader)
	{
		DC_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader readd!");
		m_Shaders[name] = shader;
	}

	S_PTR<Shader>& ShaderLibrary::Load(const std::string& path)
	{
		S_PTR<Shader> shader = Shader::Create(path);
		Add(shader);
		return shader;
	}

	S_PTR<Shader>& ShaderLibrary::Load(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
	{
		S_PTR<Shader> shader = Shader::Create(name, vertexSource, fragmentSource);
		Add(shader);
		return shader;
	}

	S_PTR<Shader> ShaderLibrary::Get(const std::string& name)
	{
		DC_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "Shader not found");
		return m_Shaders[name];
	}
}