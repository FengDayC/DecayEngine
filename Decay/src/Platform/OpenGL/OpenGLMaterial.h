#include "Renderer\Material.h"

namespace Decay
{
	class OpenGLShader;
	class Shader;

	class OpenGLMaterial : public Material 
	{
	public:
		OpenGLMaterial(S_PTR<Shader> shader,const std::string& name);

		virtual void Set(const std::string& name, int value) override;

		virtual void Set(const std::string& name, float value) override;
		virtual void Set(const std::string& name, glm::vec2 value) override;
		virtual void Set(const std::string& name, glm::vec3 value) override;
		virtual void Set(const std::string& name, int* data, uint32_t size) override;
		virtual void Set(const std::string& name, glm::mat4 value) override;

		virtual void Set(const std::string& name, S_PTR<Texture> data) override;
		virtual void Set(const std::string& name, std::vector<S_PTR<Texture>> data) override;
	
	public:
		virtual	std::string GetName() override;
		virtual S_PTR<Shader> GetShader() override;
		
	private:

		S_PTR<OpenGLShader> m_shader;
		std::string m_name;
		std::map<std::string, S_PTR<Texture>> m_textures;
		std::map<std::string, std::vector<S_PTR<Texture>>> m_textureArrays;
	};
}