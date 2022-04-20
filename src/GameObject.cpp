#include "GameObject.h"

std::list<GameObject*> GameObject::Objects;
float GameObject::ElapsedTime = 0.0f;

glm::vec3 GerstnerWave(glm::vec4 wave, glm::vec3 p, glm::vec3& tangent, glm::vec3& binormal, float time)
{
	float steepness = wave.z;
	float wavelength = wave.w;

	float k = 2.0f * glm::pi<float>() / wavelength;
	float c = glm::sqrt(9.81 / k);
	glm::vec2 direction = glm::vec2(wave.x, wave.y);
	glm::vec2 d = glm::normalize(direction);
	glm::vec2 planar = glm::vec2(p.x, p.z);
	float f = k * (glm::dot(d, planar) - c * time);
	float a = steepness / k;

	glm::vec2 f_helper_helper = glm::vec2(glm::sin(f), glm::cos(f));
	glm::vec3 f_helper = glm::vec3(f_helper_helper.x, f_helper_helper.y, f_helper_helper.x);
	glm::vec3 f_helper_return = glm::vec3(f_helper_helper.y, f_helper_helper.x, f_helper_helper.y);

	tangent += glm::vec3(
		1.0f - d.x * d.x,
		d.x,
		-d.x * d.y
	) * f_helper * steepness;
	binormal += glm::vec3(
		-d.x * d.y,
		d.y,
		1.0f - d.y * d.y
	) * f_helper * steepness;

	return glm::vec3(
		d.x,
		1.0f,
		d.y
	) * f_helper_return * a;
}

glm::vec3 GerstnerWaves(glm::vec3 pos, glm::vec3& normal, float time)
{
	const glm::vec4 WaveA = glm::vec4(1, 1, 0.25, 20);
	const glm::vec4 WaveB = glm::vec4(1, .6, .25, 11);
	const glm::vec4 WaveC = glm::vec4(1, 1.3, .25, 8);
	glm::vec3 tangent = glm::vec3(1, 0, 0);
	glm::vec3 binormal = glm::vec3(0, 0, 1);
	glm::vec3 p = pos;
	p += GerstnerWave(WaveA, pos, tangent, binormal, time);
	p += GerstnerWave(WaveB, pos, tangent, binormal, time);
	p += GerstnerWave(WaveC, pos, tangent, binormal, time);

	normal = glm::normalize(glm::cross(binormal, tangent));
	return p;
}
