#pragma once
#include <glm\glm.hpp>

namespace Decay
{
	class Texture;
	class Shader;

	class Material
	{
	public:
		~Material();

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual void Set(const std::string& name, int value) = 0;
		virtual void Set(const std::string& name, float value) = 0;
		virtual void Set(const std::string& name, glm::vec2 value) = 0;
		virtual void Set(const std::string& name, glm::vec3 value) = 0;
		virtual void Set(const std::string& name, int* data, uint32_t size) = 0;
		virtual void Set(const std::string& name, glm::mat4 value) = 0;

		virtual void Set(const std::string& name, S_PTR<Texture> data) = 0;
		virtual void Set(const std::string& name, std::vector<S_PTR<Texture>> data) = 0;
	
		static S_PTR<Material> Create(S_PTR<Shader> shader,const std::string& name);
	public:
		virtual	std::string GetName() = 0;
		virtual S_PTR<Shader> GetShader() = 0;

	};
}