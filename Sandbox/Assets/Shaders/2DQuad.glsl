#stage vertex
#version 330 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_uv;
layout(location = 3) in float a_textureIndex;
layout(location = 4) in float a_tilling;

uniform mat4 decay_camera_projectionMatrix;
uniform mat4 decay_camera_viewMatrix;

out vec4 v_color;
out vec2 v_uv;
out float v_textureIndex;
out float v_tilling;

void main()
{
	gl_Position = decay_camera_projectionMatrix*decay_camera_viewMatrix*vec4(a_pos,1.0f);
	v_color = a_color;
	v_uv = a_uv;
	v_textureIndex = a_textureIndex;
	v_tilling = a_tilling;
}

#stage fragment
#version 330 core

in vec4 v_color;
in vec2 v_uv;
in float v_textureIndex;
in float v_tilling;

uniform sampler2D u_textures[32];

out vec4 fragColor;

void main()
{
	fragColor = texture(u_textures[uint(v_textureIndex)],v_uv*v_tilling)*v_color;
	//fragColor = vec4(v_uv,0.0,1.0);
}