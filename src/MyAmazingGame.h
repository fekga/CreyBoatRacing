#pragma once

#include "Camera.h"
#include "Shader.h"
#include "GameObject.h"

class MyAmazingGame
{
public:
	MyAmazingGame() = default;
	~MyAmazingGame() = default;

public:
	void preInit( sf::Framework< MyAmazingGame >& iFramework );
	void postInit( sf::Framework< MyAmazingGame >& iFramework );
	void processInput(sf::Framework< MyAmazingGame >& iFramework, double deltaTime);
	void step( sf::Framework< MyAmazingGame >& iFramework, double deltaTime );

private:
	const GLfloat NEAR_PLANE = 0.1f;
	const GLfloat FAR_PLANE = 1000.0f;
	const glm::vec3 color = { 0.53f, 0.71f, 0.92f };

	double timeElapsed = 0.;

	Camera camera_ = Camera(glm::vec3(0.0f, 5.0f, -5.0f)*3.0f);
	Shader ourShader_;


	std::vector<GameObject*> objects;
	GameObject* gameObject = nullptr;
};