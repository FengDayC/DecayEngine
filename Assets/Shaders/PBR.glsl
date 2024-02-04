#stage vertex
#version 430 compatibility
#extension GL_ARB_shading_language_include : require
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_TexCood;
layout(location = 2) in vec3 a_Normal;
layout(location = 3) in vec3 a_Bitangent;
layout(location = 4) in vec3 a_Tangent;

struct VertexOutput
{
	vec3 Position;
	vec3 TexCood;
	vec3 Normal;
	vec3 Bitangent;
	vec3 Tangent;
};

out VertexOutput v_Out;

//Uniforms
uniform mat4 decay_camera_matrix;

void main()
{
	v_Out.Position = a_Position;
	v_Out.TexCood = a_TexCood;
	v_Out.Normal = a_Normal;
	v_Out.Bitangent = a_Bitangent;
	v_Out.Tangent = a_Tangent;
	gl_Position = decay_camera_matrix*vec4(v_Out.Position,1.0);
}

#stage fragment
#version 430 compatibility
#extension GL_ARB_shading_language_include : require
#include "/include/BRDF.glslinc"
#include "/include/Lighting.glslinc"

struct VertexOutput
{
	vec3 Position;
	vec3 TexCood;
	vec3 Normal;
	vec3 Bitangent;
	vec3 Tangent;
};

struct MaterialUniforms
{
	vec3 AlbedoColor;
	vec3 Emission;
	bool UseNormalMap;
	float Roughness;
	float Metalness;
	float Reflectance;
};

in VertexOutput v_Out;

out vec4 fragColor;

uniform MaterialUniforms u_MaterialUniforms;
uniform sampler2D u_AlbedoTexture;
uniform sampler2D u_NormalTexture;
uniform sampler2D u_RoughnessTexture;
uniform sampler2D u_MetalnessTexture;

void main()
{
	fragColor = vec4(1.0,.0,1.0,1.0);
}

