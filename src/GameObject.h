#pragma once

#include "Mesh.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

#include <list>

#include "Camera.h"
#include "Shader.h"

glm::vec3 GerstnerWave(glm::vec4 wave, glm::vec3 p, glm::vec3& tangent, glm::vec3& binormal, float time);

glm::vec3 GerstnerWaves(glm::vec3 pos, glm::vec3& normal, float time);
	


class GameObject
{
public:

	static std::list<GameObject*> Objects;
	static float ElapsedTime;

	GameObject()
	{
		Objects.push_back(this);
	}

	virtual ~GameObject()
	{
		Objects.remove(this);
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

	virtual bool initDone()
	{
		// First call return false, subsequent calls return true
		// Call this in inherited children
		static bool initCalled = false;
		if (!initCalled)
			return false;
		initCalled = true;
		return true;
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
	}

	glm::vec3 position_ = glm::vec3(0.0f);
	glm::vec3 scale_ = glm::vec3(1.0f);
};

