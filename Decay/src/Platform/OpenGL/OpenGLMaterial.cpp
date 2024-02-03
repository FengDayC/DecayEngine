#include "OpenGLMaterial.h"
#include "OpenGLShader.h"

Decay::OpenGLMaterial::OpenGLMaterial(S_PTR<Shader> shader,const std::string& name) 
	:  m_Name(name)
{
	m_Shader = std::dynamic_pointer_cast<OpenGLShader>(shader);
}

Decay::OpenGLMaterial::~OpenGLMaterial()
{
}

void Decay::OpenGLMaterial::Bind()
{
	m_Shader->Bind();
}

void Decay::OpenGLMaterial::UnBind()
{
	m_Shader->UnBind();
}

void Decay::OpenGLMaterial::Set(const std::string& name, int value)
{
	m_Shader->SetInt(name, value);
}

void Decay::OpenGLMaterial::Set(const std::string& name, float value)
{
	m_Shader->SetFloat(name, value);
}

void Decay::OpenGLMaterial::Set(const std::string& name, glm::vec2 value)
{
	m_Shader->SetFloat2(name, value);
}

void Decay::OpenGLMaterial::Set(const std::string& name, glm::vec3 value)
{
	m_Shader->SetFloat3(name, value);
}

void Decay::OpenGLMaterial::Set(const std::string& name, int* data, uint32_t size)
{
	m_Shader->SetIntArray(name, data, size);
}

void Decay::OpenGLMaterial::Set(const std::string& name, glm::mat4 value)
{
	m_Shader->SetMatrix4(name, value);
}

void Decay::OpenGLMaterial::Set(const std::string& name, S_PTR<Texture> data)
{
	m_Textures[name] = data;
}

void Decay::OpenGLMaterial::Set(const std::string& name, std::vector<S_PTR<Texture>> data)
{
	m_TextureArrays[name] = data;
}


std::string Decay::OpenGLMaterial::GetName()
{
	return m_Name;
}

S_PTR<Decay::Shader> Decay::OpenGLMaterial::GetShader()
{
	return m_Shader;
}
