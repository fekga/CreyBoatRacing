#pragma once

#include "Mesh.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

#include "Camera.h"

class GameObject
{
public:
	void setData()
	{
		mesh_.generateTerrain(2000);
		//mesh_.generateCube();
		//mesh_.generatePlane();
	}

	void render()
	{
		mesh_.render();
		//mesh_.renderCube();
	}

	void update(float deltaTime)
	{
		angle_ = glm::atan(velocity_.z, velocity_.x);
		////movement_ = glm::rotateY(movement_, angle);
		////acceleration_ = movement_ * deltaTime;
		//velocity_ += movement_ * deltaTime;
		//// constrain speed
		//if (glm::length(velocity_) > max_speed_)
		//{
		//	velocity_ = glm::normalize(velocity_) * max_speed_;
		//}
		position_ += movement_ * deltaTime;
	}

	void updateCamera(Camera& camera, float deltaTime) const
	{
		//glm::vec3 velocityNormalized = velocity_;
		//if (glm::length(velocityNormalized) > 0.0f)
		//	velocityNormalized = glm::normalize(velocityNormalized);
		glm::vec3 newPos = position_ + glm::vec3(0.0f,1.f,-1.5f) * 25.0f;
		camera.Position = newPos;
		camera.Target = position_;
	}

	glm::mat4 getModelMatrix() const;

	void setMovement(const glm::vec3& movement) { movement_ = movement * speed_; }

	
	Mesh mesh_;
	glm::mat4 model_ = glm::mat4(1.0f);

	glm::vec3 position_ = glm::vec3(0.0f);
	glm::vec3 velocity_ = glm::vec3(0.0f,0.0f,1.0f);
	glm::vec3 acceleration_ = glm::vec3(0.0f);
	glm::vec3 movement_ = glm::vec3(0.0f);
	glm::float32 angle_ = 0.0f;
	glm::float32 speed_ = 10.0f;
	glm::float32 max_speed_ = 3.0f;

	glm::vec3 scale_ = glm::vec3(1.0f);
};

