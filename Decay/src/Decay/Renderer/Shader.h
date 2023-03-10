#pragma once

#include<glm\glm.hpp>

namespace Decay
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;

		virtual void UnBind() const = 0;

		virtual std::string GetName() const = 0;

	public:
		static S_PTR<Shader> Create(const std::string& path);
		static S_PTR<Shader> Create(const std::string& name,const std::string& vertexSource, const std::string& fragmentSource);
	};

	class ShaderLibrary
	{
	public:
		void Add(const S_PTR<Shader>& shader);

		void Add(const std::string& name,const S_PTR<Shader>& shader);

		S_PTR<Shader>& Load(const std::string& path);

		S_PTR<Shader>& Load(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);

		S_PTR<Shader> Get(const std::string& name);

		inline bool Exists(const std::string& name) const { return m_Shaders.find(name) != m_Shaders.end(); }
	private:
		std::unordered_map<std::string, S_PTR<Shader>> m_Shaders;
	};
}
