#pragma once
#include "GameObject.h"

class Buoy :
    public GameObject
{


	virtual void v_init()
	{
		shader_.load("asset/shaders/model_loading.vs", "asset/shaders/model_loading.fs");
		model_ = EntityModel::LoadModel("asset/models/buoy.obj");
		scale_ = glm::vec3(2.0f);
	}
public:
	void update(float deltaTime)
	{
		glm::vec3 normal;
		translate_offset_ = GerstnerWaves(GameObject::Waves, position_, normal, GameObject::ElapsedTime);
	}

	void render(const Camera& camera, float timeElapsed)
	{
		preRender(shader_,camera);

		shader_.setFloat("time", timeElapsed);

		if(model_)
			model_->Draw(shader_);

		shader_.deactivate();
	}

private:
	glm::mat4 getModelMatrix() const
	{
		glm::mat4 model = glm::mat4(1.0f);
		// order is important
		model = glm::translate(model, position_ + translate_offset_);
		model = glm::scale(model, scale_);
		return model;
	}

	glm::vec3 translate_offset_;

	static Shader shader_;
	EntityModel* model_ = nullptr;
};

