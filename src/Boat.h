#pragma once
#include "GameObject.h"

#include <glm/gtx/polar_coordinates.hpp>

#include <windows.h>

void clearscreen();

class Boat :
    public GameObject
{
public:
	bool initDone()
	{
		bool initCalled = GameObject::initDone();
		if (!initCalled)
		{
			shader_.load("asset/shaders/simple.vs", "asset/shaders/simple.fs");
			mesh_.generateCube();
			scale_ = glm::vec3(3.0f, 3.0f, 10.0f);
		}
		return initCalled;
	}

	void updateCamera(Camera& camera, float deltaTime) const 
	{
		glm::vec3 pos = position_;
		glm::vec2 euc = glm::vec2(glm::cos(angle_), glm::sin(angle_));
		glm::vec3 offset = glm::vec3(euc.y, 0.0f, euc.x);
		pos -= offset * 40.0f;
		pos.y = 20.f;
		camera.Position = pos;// +translate_offset_;
		camera.Target = position_ + offset * 10.0f;
	}

	void update(float deltaTime)
	{
		//FIXME angle changes rapidly at slow velocity

		// only move when going forward or backwards (and not only to the sides)
		if (abs(movement_.z) != 0.0f)
		{
			movement_ = glm::rotateY(movement_, angle_);
			acceleration_ = movement_;
		}
		else
		{
			acceleration_ *= 0.0f;
		}
		velocity_ += acceleration_ * deltaTime;
		// constrain speed
		if (glm::length(velocity_) > max_velocity_)
		{
			velocity_ = glm::normalize(velocity_) * max_velocity_;
		}
		velocity_ = velocity_ * 0.975f;
		if (glm::length(velocity_) > 0.0f)
			angle_ = glm::atan(velocity_.x, velocity_.z);
		position_ += velocity_ * deltaTime;
		//std::cout 
		//	<< "\nBoat:"
		//	<< "\nAngle: " << angle_
		//	<< "\nMovement: " << movement_.x << ", " << movement_.z
		//	<< "\nVelocity: " << velocity_.x << ", " << velocity_.z
		//	<< "\nAcceleration: " << acceleration_.x << ", " << acceleration_.z
		//	<< std::endl;

		glm::vec3 normal;
		translate_offset_ = GerstnerWaves(position_, normal, GameObject::ElapsedTime);
		
		//position_.y = glm::sin(GameObject::ElapsedTime * 3.0f) * 5.0f + 3.0f;
		//angle_ = GameObject::ElapsedTime;
	}

	void setMovement(glm::vec3& movement) 
	{ 
		if (movement.z == 0.0f)
			movement *= 0.0f;
		if (movement.z < 0.0f)
			movement.z *= 0.5f;
		movement.x *= 2.0f;
		movement_ = movement * movement_speed_;
	}

	void render(const Camera& camera, float timeElapsed)
	{
		preRender(shader_, camera);

		shader_.setFloat("time", timeElapsed);

		mesh_.render();

		shader_.deactivate();
	}

private:
	virtual glm::mat4 getModelMatrix() const
	{
		glm::mat4 model = glm::mat4(1.0f);
		// order is important
		model = glm::translate(model, position_ + translate_offset_);
		model = glm::rotate(model, angle_, glm::vec3(0, 1, 0));
		model = glm::scale(model, scale_);
		return model;
	}

	glm::vec3 velocity_ = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 acceleration_ = glm::vec3(0.0f);
	glm::vec3 movement_ = glm::vec3(0.0f);
	glm::float32 angle_ = 0.0f;
	glm::float32 movement_speed_ = 10.0f;
	glm::float32 max_velocity_ = 50.0f;

	glm::vec3 translate_offset_ = glm::vec3(0.0f);

	Shader shader_;
	Mesh mesh_;
};

