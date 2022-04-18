#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec2 v_texCoord;
out vec3 v_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float time;

void main()
{
	vec4 pos = vec4(position, 1.0);
	//pos.y -= sin(time + float(gl_VertexID))*5.;
	gl_Position = projection * view * model * pos;
	v_texCoord = texCoord;
	v_normal = (model * vec4(normal,1)).xyz;
}