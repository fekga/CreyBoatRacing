#pragma once
#include "GameObject.h"

class Water :
    public GameObject
{
	void v_init()
	{
		if (!shader_.ID)
		{
			shader_.load("asset/shaders/water.vs", "asset/shaders/water.fs");
			mesh_.generateTerrain(2000);
		}
	}
public:
    void render(const Camera& camera, float timeElapsed)
    {
		preRender(shader_, camera);

		shader_.setVec4("WaveA", GameObject::Waves[0]);
		shader_.setVec4("WaveB", GameObject::Waves[1]);
		shader_.setVec4("WaveC", GameObject::Waves[2]);

		shader_.setFloat("time", timeElapsed);

		mesh_.render();

		shader_.deactivate();
    }

private:
    static Shader shader_;
	static Mesh mesh_;
};

