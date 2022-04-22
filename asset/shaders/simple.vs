#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 v_normal;
out vec3 v_fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float time;

void main()
{
	// position is a coordinate so the 4th value is 1
	gl_Position = projection * view * model * vec4(position, 1.0);
	// normal is a direction so the 4th value is 0
	v_normal = (model * vec4(normal,0)).xyz;
	v_fragPos = (model * vec4(position,1)).xyz;
}