#pragma once
#include "GameObject.h"

#include <glm/gtc/random.hpp>

class Coin :
    public GameObject
{

	void v_init()
	{
		shader_.load("asset/shaders/model_loading.vs", "asset/shaders/model_loading.fs");
		model_ = EntityModel::LoadModel("asset/models/coin.obj");

		// move upwards
		translate_offset_ = glm::vec3(0, 10, 0);

		//add initial random rotation
		rotate_offset_ = glm::linearRand(0.0f, glm::pi<float>() * 2.0f);
		scale_ = glm::vec3(1.0f);
	}
public:
	void update(float deltaTime)
	{
		rotate_offset_ += glm::pi<float>() * 2.0f * deltaTime / 2.0f;
		glm::vec3 normal;
		wave_offset_ = GerstnerWaves(GameObject::Waves, position_, normal, GameObject::ElapsedTime);
		wave_offset_.x = 0.0f;
		wave_offset_.z = 0.0f;
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
		model = glm::translate(model, position_ + translate_offset_ + wave_offset_);
		model = glm::rotate(model, rotate_offset_, glm::vec3(0, 1, 0));
		model = glm::scale(model, scale_);
		return model;
	}

	glm::vec3 translate_offset_;
	glm::vec3 wave_offset_;
	glm::float32 rotate_offset_;

	Shader shader_;
	EntityModel* model_ = nullptr;
};

