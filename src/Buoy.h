#pragma once
#include "GameObject.h"


class Buoy :
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
		}
		return initCalled;
	}

	void render(const Camera& camera, float timeElapsed)
	{
		preRender(shader_,camera);

		shader_.setFloat("time", timeElapsed);

		mesh_.render();

		shader_.deactivate();
	}

private:


	static Shader shader_;
	static Mesh mesh_;
};

