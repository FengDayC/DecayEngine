#include "OpenGLMaterial.h"
#include "OpenGLShader.h"

Decay::OpenGLMaterial::OpenGLMaterial(S_PTR<Shader> shader,const std::string& name) 
	:  m_name(name)
{
	m_shader = std::dynamic_pointer_cast<OpenGLShader>(shader);
}

void Decay::OpenGLMaterial::Set(const std::string& name, int value)
{
	m_shader->SetInt(name, value);
}

void Decay::OpenGLMaterial::Set(const std::string& name, float value)
{
	m_shader->SetFloat(name, value);
}

void Decay::OpenGLMaterial::Set(const std::string& name, glm::vec2 value)
{
	m_shader->SetFloat2(name, value);
}

void Decay::OpenGLMaterial::Set(const std::string& name, glm::vec3 value)
{
	m_shader->SetFloat3(name, value);
}

void Decay::OpenGLMaterial::Set(const std::string& name, int* data, uint32_t size)
{
	m_shader->SetIntArray(name, data, size);
}

void Decay::OpenGLMaterial::Set(const std::string& name, glm::mat4 value)
{
	m_shader->SetMatrix4(name, value);
}

void Decay::OpenGLMaterial::Set(const std::string& name, S_PTR<Texture> data)
{
	m_textures[name] = data;
}

void Decay::OpenGLMaterial::Set(const std::string& name, std::vector<S_PTR<Texture>> data)
{
	m_textureArrays[name] = data;
}


std::string Decay::OpenGLMaterial::GetName()
{
	return m_name;
}

S_PTR<Decay::Shader> Decay::OpenGLMaterial::GetShader()
{
	return m_shader;
}
