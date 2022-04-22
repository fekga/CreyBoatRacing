#pragma once

#include "Camera.h"
#include "Shader.h"

#include "GameObject.h"

#include "Water.h"
#include "Boat.h"
#include "Buoy.h"
#include "Coin.h"

// irrklang for sound
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
	void collisionDetection();
	void removeDead();
	void logic();
	void render();

private:
	const glm::vec3 color = { 0.53f, 0.71f, 0.92f };

	double timeElapsed = 0.;
	bool gameWon = false;

	Camera camera_ = Camera(glm::vec3(0.0f, 5.0f, -5.0f)*30.0f);

	Water* water_;
	Boat* boat_;
	std::list<Buoy*> buoys;
	std::list<Coin*> coins;

	//TODO move this into a SoundManager class
	irrklang::ISoundEngine* SoundEngine = nullptr;
	irrklang::ISound* Music = nullptr;
	irrklang::ISound* BoatEngineSound = nullptr;
	irrklang::ISoundSource* BoatEngineSoundSource = nullptr;
	irrklang::ISound* CoinSound = nullptr;
	irrklang::ISoundSource* CoinSoundSource = nullptr;
	irrklang::ISound* GameWinSound = nullptr;
	irrklang::ISoundSource* GameWinSoundSource = nullptr;

	
};