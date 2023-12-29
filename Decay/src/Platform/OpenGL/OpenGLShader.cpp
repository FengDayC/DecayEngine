#include "dcpch.h"
#include "OpenGLShader.h"
#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include "Decay\Profile\Instrumentor.hpp"

namespace Decay
{

	OpenGLShader::OpenGLShader(const std::string& path)
	{
		DC_PROFILE_FUNCTION();
		std::string sourceCode = ReadFile(path);
		auto sources = PreProcess(sourceCode);
		Compile(sources);

		auto lastSlash = path.find_last_of("/\\");
		lastSlash = (lastSlash == std::string::npos) ? 0 : lastSlash + 1;
		auto lastDot = path.rfind('.');
		int count = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;
		m_Name = path.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
		: m_Name(name)
	{
		DC_PROFILE_FUNCTION();
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSource;
		sources[GL_FRAGMENT_SHADER] = fragmentSource;
		Compile(sources);
	}
	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererId);
	}

	void OpenGLShader::Bind() const
	{
		DC_PROFILE_FUNCTION();
		glUseProgram(m_RendererId);
	}

	void OpenGLShader::UnBind() const
	{
		DC_PROFILE_FUNCTION();
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		UploadUniformFloat(name, value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
	{
		UploadUniformFloat2(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetMatrix4(const std::string& name, const glm::mat4& value)
	{
		UploadUniformMatrix4(name, value);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, glm::vec4 value) const
	{
		GLuint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform4fv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::UploadUniformMatrix4(const std::string& name, glm::mat4 matrix) const
	{
		GLuint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value) const
	{
		GLuint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform1i(location, value);
	}
	void Decay::OpenGLShader::UploadUniformFloat(const std::string& name, float value) const
	{
		GLuint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform1f(location, value);
	}
	void Decay::OpenGLShader::UploadUniformFloat2(const std::string& name, glm::vec2 value) const
	{
		GLuint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform2fv(location, 1, glm::value_ptr(value));
	}
	void Decay::OpenGLShader::UploadUniformFloat3(const std::string& name, glm::vec3 value) const
	{
		GLuint location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform3fv(location, 1, glm::value_ptr(value));
	}
	std::string OpenGLShader::ReadFile(const std::string& path)
	{
		DC_PROFILE_FUNCTION();
		std::string content;
		std::ifstream in(path, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			content.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&content[0], content.size());
			in.close();
		}
		else
		{
			DC_CORE_ERROR("Cannot load file \"{0}\"", path);
		}

		return content;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& sourceCode)
	{
		DC_PROFILE_FUNCTION();
		std::unordered_map<GLenum, std::string> shaderSources;
		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = sourceCode.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = sourceCode.find_first_of("\r\n", pos);
			DC_CORE_ASSERT(eol != std::string::npos, "Shader synax error!");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = sourceCode.substr(begin, eol - begin);
			DC_CORE_ASSERT(type == "vertex" || type == "fragment", "Unexpected shader type");

			size_t nxtLinePos = sourceCode.find_first_not_of("\r\n", eol);
			pos = sourceCode.find(typeToken, nxtLinePos);

			shaderSources[ShaderTypeFromString(type)] = sourceCode.substr(nxtLinePos, pos - (nxtLinePos == std::string::npos ? sourceCode.size() - 1 : nxtLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& sourceCode)
	{
		DC_PROFILE_FUNCTION();

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		GLuint program = glCreateProgram();

		std::vector<GLenum> shaderIds;
		shaderIds.reserve(sourceCode.size());

		for (auto& p : sourceCode)
		{
			GLenum type = p.first;
			std::string sourceCode = p.second;

			// Create an empty vertex shader handle
			GLuint shader = glCreateShader(type);

			// Send the vertex shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* source = (const GLchar*)sourceCode.c_str();
			glShaderSource(shader, 1, &source, 0);

			// Compile the vertex shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				DC_CORE_ERROR("{0}", infoLog.data());
				DC_CORE_ASSERT(false, "Shader compile failed!");

				break;
			}
			glAttachShader(program, shader);
			shaderIds.push_back(shader);
		}

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);

			for (GLenum id : shaderIds)
			{
				glDeleteShader(id);
			}


			DC_CORE_ERROR("{0}", infoLog.data());
			DC_CORE_ASSERT(false, "Shader link failed!");

			return;
		}

		for (GLenum id : shaderIds)
		{
			glDetachShader(program, id);
		}

		m_RendererId = program;
	}

	GLenum OpenGLShader::ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
		{
			return GL_VERTEX_SHADER;
		}
		else if (type == "fragment")
		{
			return GL_FRAGMENT_SHADER;
		}
		DC_CORE_ASSERT(false, "Unsupported shader type!");
		return 0;
	}
}