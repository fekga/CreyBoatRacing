#pragma once
#include "GameObject.h"

class Water :
    public GameObject
{
public:
	bool initDone()
	{
		bool initCalled = GameObject::initDone();
		if (!initCalled)
		{
			shader_.load("asset/shaders/water.vs", "asset/shaders/water.fs");
			mesh_.generateTerrain(2000);
		}
		return initCalled;
	}

    void render(const Camera& camera, float timeElapsed)
    {
		preRender(shader_, camera);

		//TODO don't forget to turn movement on
		shader_.setFloat("time", timeElapsed);

		mesh_.render();

		shader_.deactivate();
    }

private:
	

    static Shader shader_;
	static Mesh mesh_;
};

