#pragma once

#include "Camera.h"
#include "Shader.h"
#include "GameObject.h"

#include "Water.h"
#include "Boat.h"

#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

class MyAmazingGame
{
public:
	MyAmazingGame() = default;
	~MyAmazingGame();

public:
	void preInit( sf::Framework< MyAmazingGame >& iFramework );
	void postInit( sf::Framework< MyAmazingGame >& iFramework );
	void processInput(sf::Framework< MyAmazingGame >& iFramework, double deltaTime);
	void step( sf::Framework< MyAmazingGame >& iFramework, double deltaTime );
	void update(double deltaTime );
	void render();

private:
	const glm::vec3 color = { 0.53f, 0.71f, 0.92f };

	double timeElapsed = 0.;

	Camera camera_ = Camera(glm::vec3(0.0f, 5.0f, -5.0f)*30.0f);

	Water water_;
	Boat boat_;

	irrklang::ISoundEngine* SoundEngine = nullptr;
	irrklang::ISound* Music = nullptr;
	irrklang::ISound* BoatEngineSound = nullptr;
	irrklang::ISoundSource* BoatEngineSoundSource = nullptr;
};