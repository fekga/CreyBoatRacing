#include "GameObject.h"

glm::mat4 GameObject::getModelMatrix() const
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, scale_);
	//model = glm::rotate(model, angle_, glm::vec3(0, 1, 0));
	model = glm::translate(model, position_);
	return model;
}