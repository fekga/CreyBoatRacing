#version 330 core
out vec4 fragColor;

in vec2 v_texCoord;
in vec3 v_normal;

void main()
{
	fragColor = vec4(v_texCoord,0,1);
}