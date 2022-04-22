#pragma once

#include "Mesh.h"

#include "EntityModel.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/io.hpp>

#include <iostream>
#include <vector>

#include "Camera.h"
#include "Shader.h"

glm::vec3 GerstnerWave(const glm::vec4& wave, const glm::vec3& p, glm::vec3& tangent, glm::vec3& binormal, const float& time);

glm::vec3 GerstnerWaves(const std::vector<glm::vec4>& waves, const glm::vec3& pos, glm::vec3& normal, const float& time);

class GameObject
{
public:

	static std::vector<GameObject*> Objects;
	static float ElapsedTime;
	static glm::vec3 SunPosition;
	static std::vector<glm::vec4> Waves;

	bool is_dead = false;
	GameObject()
	{
		
	}
	virtual ~GameObject()
	{
		is_dead = true;
	}
public:
	template<typename T>
	static T* create()
	{
		T* t = new T();
		Objects.push_back(t);
		return t;
	}

	// no copy operations
	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;
	// no move operations
	GameObject(GameObject&&) = delete;
	GameObject& operator=(GameObject&&) = delete;

	
	virtual void updateCamera(Camera& camera, float deltaTime) const {}

	virtual void update(float deltaTime) {}

	virtual void render(const Camera& camera, float timeElapsed) = 0;

	virtual glm::mat4 getModelMatrix() const
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position_);
		model = glm::scale(model, scale_);
		return model;
	}

	void init()
	{
		if (!init_flag)
		{
			v_init();
			init_flag = true;
		}
	}

	glm::vec3 getPosition() const
	{
		return position_;
	}

	void setPosition(const glm::vec3& newPos)
	{
		position_ = newPos;
	}

protected:
	virtual void preRender(const Shader& shader, const Camera& camera)
	{
		shader.activate();

		// pass projection matrix to shader (note that in this case it could change every frame)
		glm::mat4 projection = camera.GetProjectionMatrix();
		shader.setMat4("projection", projection);

		// camera/view transformation
		glm::mat4 view = camera.GetViewMatrix(true);
		shader.setMat4("view", view);

		glm::mat4 model = getModelMatrix();
		shader.setMat4("model", model);

		shader.setVec3("viewPos", camera.Position);

		shader.setVec3("sunPosition", SunPosition);
	}

	glm::vec3 position_ = glm::vec3(0.0f);
	glm::vec3 scale_ = glm::vec3(1.0f);


	virtual void v_init() = 0;
private:
	bool init_flag = false;
};

