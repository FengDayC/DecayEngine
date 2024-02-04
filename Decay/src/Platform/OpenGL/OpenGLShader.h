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
		void SetInt(const std::string& name, int value) override;
		void SetIntArray(const std::string& name,int* values, const uint32_t count) override;
		void SetFloat(const std::string& name, float value) override;
		void SetFloat2(const std::string& name, const glm::vec2& value) override;
		void SetFloat3(const std::string& name, const glm::vec3& value) override;
		void SetFloat4(const std::string& name, const glm::vec4& value) override;
		void SetMatrix4(const std::string& name, const glm::mat4& value) override;

	public:
		void UploadUniformMatrix4(const std::string& name, glm::mat4 matrix) const;
		void UploadUniformInt(const std::string& name, int value) const;
		void UploadUniformIntArray(const std::string& name,int* value, const uint32_t count) const;
		void UploadUniformFloat(const std::string& name, float value) const;
		void UploadUniformFloat2(const std::string& name, glm::vec2 value) const;
		void UploadUniformFloat3(const std::string& name, glm::vec3 value) const;
		void UploadUniformFloat4(const std::string& name, glm::vec4 value) const;

	private:
		std::string ReadFile(const std::string& path);
		std::unordered_map<GLenum ,std::string> PreProcess(const std::string& sourceCode);
		void OpenGLShader::ProcessIncludeFiles(const std::string& glsl_code, std::unordered_map<std::string, std::string>& includeFiles);
		void Compile(const std::unordered_map<GLenum, std::string>& sourceCode);

	private:
		static GLenum ShaderTypeFromString(const std::string& type);

	private:
		uint32_t m_RendererId;

		std::string m_Name;
	};
}