#include "dcpch.h"
#include "Material.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform\OpenGL\OpenGLMaterial.h"

S_PTR<Decay::Material> Decay::Material::Create(S_PTR<Shader> shader,const std::string& name)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::None:
		DC_CORE_ERROR("No Renderer API");
		break;
    case RendererAPI::API::OpenGL:
        return CreateS_PTR<OpenGLMaterial>(shader, name);

    default:
        DC_CORE_ERROR("Unsupported Renderer API");
        break;
    }
    return nullptr;
}
