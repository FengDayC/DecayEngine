#pragma once

#include<glm\glm.hpp>

namespace Decay
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		~Shader();

		void Bind() const;

		void UnBind() const;

	public:
		void SetUniformMatrix4(const std::string& name,glm::mat4 matrix) const;

	private:
		uint32_t m_RendererId;
	};
}
