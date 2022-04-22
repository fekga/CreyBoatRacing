#pragma once
#include "GameObject.h"

class Boat :
    public GameObject
{

	void v_init() override
	{
		shader_.load("asset/shaders/model_loading.vs", "asset/shaders/model_loading.fs");
		model_ = EntityModel::LoadModel("asset/models/speedboat.obj");
		scale_ = glm::vec3(1.0f);
		// only used when model is facing wrong direction
		// in blender, use +Z forward to make it face correctly
		rotate_offset_ = 0.0f;
	}
public:
	void updateCamera(Camera& camera, float deltaTime) const 
	{
		glm::vec3 pos = position_;
		glm::vec2 euc = glm::vec2(glm::cos(angle_), glm::sin(angle_));
		glm::vec3 offset = glm::vec3(euc.y, 0.0f, euc.x);
		pos -= offset * 100.0f;
		pos.y = 40.f;
		camera.Position = pos;
		camera.Target = position_ + offset * 20.0f;
	}

	void update(float deltaTime)
	{
		movement_ = glm::rotateY(movement_, angle_);
		

		acceleration_ = movement_;

		float speed = glm::length(velocity_);

		velocity_ += acceleration_ * deltaTime;
		
		if (speed > 0.15f)
		{
			angle_ = glm::atan(velocity_.x, velocity_.z);
		}
		velocity_ *= 0.985f;
		
		position_ += velocity_ * deltaTime;

		translate_offset_ = GerstnerWaves(GameObject::Waves, position_, normal_, GameObject::ElapsedTime);
		// reduce offset when speed is higher
		float speed_ratio = glm::min(speed, max_velocity_) / max_velocity_;
		float wave_translation_modifierY = (1.0f - glm::pow(speed_ratio, 1.0f / 4.0f) * 0.75f);
		translate_offset_ *= glm::vec3(0.0f, wave_translation_modifierY, 0.0f);
	}

	void setMovement(const glm::vec3& movement) 
	{ 
		movement_ = movement;
		if (movement_.z == 0.0f)
			movement_ *= 0.0f;
		movement_ *= movement_speed_;
	}

	void render(const Camera& camera, float timeElapsed)
	{
		preRender(shader_, camera);

		shader_.setFloat("time", timeElapsed);

		model_->Draw(shader_);

		shader_.deactivate();
	}

private:
	glm::mat4 getModelMatrix() const
	{
		glm::mat4 model = glm::mat4(1.0f);
		// order is important
		model = glm::translate(model, position_ + translate_offset_);
		model = glm::rotate(model, angle_ + rotate_offset_, glm::vec3(0, 1, 0));
		//TODO add rotation to match wave normal
		model = glm::scale(model, scale_);
		return model;
	}

	glm::vec3 velocity_ = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 acceleration_ = glm::vec3(0.0f);
	glm::vec3 movement_ = glm::vec3(0.0f);
	glm::float32 angle_ = 0.0f;
	glm::float32 movement_speed_ = 80.0f;
	glm::float32 max_velocity_ = 550.0f;

	glm::vec3 normal_ = glm::vec3(0,1,0);
	glm::vec3 translate_offset_ = glm::vec3(0.0f);
	glm::float32 rotate_offset_ = 0.0f;

	Shader shader_;
	EntityModel* model_ = nullptr;
};

