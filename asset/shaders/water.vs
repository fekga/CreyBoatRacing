#version 330 core
layout (location = 0) in vec3 position;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 viewPos;

uniform float time;

const float pi = acos(-1.0);

uniform vec4 WaveA = vec4(1,1,0.25,20);
uniform vec4 WaveB = vec4(1,.6,.25,11);
uniform vec4 WaveC = vec4(1,1.3,.25,8);

vec3 GerstnerWave(vec4 wave, vec3 p, inout vec3 tangent, inout vec3 binormal)
{
    float steepness = wave.z;
    float wavelength = wave.w;

    float k = 2.0 * pi / wavelength;
    float c = sqrt(9.81 / k);
    vec2 d = normalize(wave.xy);
    float f = k * (dot(d,p.xz) - c * time);
    float a = steepness / k;
    
    vec2 f_helper = vec2(sin(f),cos(f));

    tangent += vec3(
        1. - d.x*d.x, 
        d.x , 
        -d.x * d.y
    ) * f_helper.xyx * steepness;
    binormal += vec3(
        -d.x * d.y,
        d.y,
        1. - d.y*d.y
    ) * f_helper.xyx * steepness;

    return vec3(
        d.x,
        1.0,
        d.y
    ) * f_helper.yxy * a;
}

void main()
{
    vec4 pos = vec4(position, 1.0);

    vec3 tangent = vec3(1,0,0);
    vec3 binormal = vec3(0,0,1);
    vec3 p = pos.xyz;

    p += GerstnerWave(WaveA, pos.xyz, tangent, binormal);
    p += GerstnerWave(WaveB, pos.xyz, tangent, binormal);
    p += GerstnerWave(WaveC, pos.xyz, tangent, binormal);
    
    vec3 normal = normalize(cross(binormal,tangent));
    
    FragPos = (model * vec4(p,1)).xyz;
    gl_Position = projection * view * vec4(FragPos,1);
    

    Normal = normal;
}