#pragma once
#include "Decay\Renderer\Shader.h"
typedef unsigned int GLenum;

namespace Decay
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& path);
		OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~OpenGLShader();

		void Bind() const override;

		void UnBind() const override;

		inline std::string GetName() const override { return m_Name; }

	public:
		void SetUniformFloat4(const std::string& name, glm::vec4 value) const;
		void SetUniformMatrix4(const std::string& name, glm::mat4 matrix) const;
		void SetUniformInt(const std::string& name, int value) const;

	private:
		std::string ReadFile(const std::string& path);
		std::unordered_map<GLenum ,std::string> PreProcess(const std::string& sourceCode);
		void Compile(const std::unordered_map<GLenum, std::string>& sourceCode);

	private:
		static GLenum ShaderTypeFromString(const std::string& type);

	private:
		uint32_t m_RendererId;

		std::string m_Name;
	};
}