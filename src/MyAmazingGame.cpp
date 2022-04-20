#include "MyAmazingGame.h"



MyAmazingGame::~MyAmazingGame()
{
	if (SoundEngine)
		SoundEngine->drop();
}

void MyAmazingGame::preInit( sf::Framework< MyAmazingGame >& iFramework )
{
	iFramework.getTextureManager().registerTextureLoader< sf::TGATextureLoader >( "tga" );

	SoundEngine = irrklang::createIrrKlangDevice();
	if (SoundEngine)
	{
		// Play music at some reasonable volume
		SoundEngine->setSoundVolume(irrklang::ik_f32(0.1f));
		Music = SoundEngine->play2D("asset/music/mixkit-crumpled-letters-1170.mp3", true, false, false, irrklang::ESM_AUTO_DETECT, true);
		BoatEngineSoundSource = SoundEngine->addSoundSourceFromFile("asset/music/ES_Pontoon Boat Fast 13 - SFX Producer.wav", irrklang::ESM_AUTO_DETECT, true);
		
		if (BoatEngineSoundSource)
		{
			BoatEngineSound = SoundEngine->play2D(BoatEngineSoundSource, true, true, false, true);
			// turn off volume initially
			if (BoatEngineSound)
				BoatEngineSound->setVolume(irrklang::ik_f32(0.0f));
		}
	}
}

void MyAmazingGame::postInit( sf::Framework< MyAmazingGame >& iFramework )
{

	// Set up camera values
	const glm::vec2 windowSize = glm::vec2(iFramework.getWindow().getWindowWidth(), iFramework.getWindow().getWindowHeight());
	const glm::float32 aspectRatio = windowSize.x / windowSize.y;

	camera_.AspectRatio = aspectRatio;


	// Initialize objects' data
	for (GameObject* obj : GameObject::Objects)
	{
		obj->initDone();
	}
}

void MyAmazingGame::step(sf::Framework< MyAmazingGame >& iFramework, double deltaTime)
{
	processInput(iFramework, deltaTime);
	update(deltaTime);
	render();

	timeElapsed += deltaTime;
	GameObject::ElapsedTime = timeElapsed;
}

void MyAmazingGame::processInput(sf::Framework< MyAmazingGame >& iFramework, double deltaTime)
{
	const glm::vec2 windowSize = glm::vec2(iFramework.getWindow().getWindowWidth(), iFramework.getWindow().getWindowHeight());
	const glm::vec2 mousePos = iFramework.getInputManager().getMousePos();
	glm::vec2 normalizedMousePos = (glm::float32(2.) * mousePos - windowSize) / windowSize;


	glm::vec3 movement = glm::vec3(0.0f);
	if (iFramework.getInputManager().isRepeat("up"))
	{
		movement.z += 1.0f;
	}
	if (iFramework.getInputManager().isRepeat("down"))
	{
		movement.z -= 1.0f;
	}
	if (iFramework.getInputManager().isRepeat("left"))
	{
		movement.x += 1.0f;
	}
	if (iFramework.getInputManager().isRepeat("right"))
	{
		movement.x -= 1.0f;
	}

	bool engineRunning = false;
	if (glm::length(movement) > 0.0f)
	{
		movement = glm::normalize(movement);
		if(movement.z != 0.0f)
			engineRunning = true;
	}

	if (engineRunning)
	{
		// Start engine
		if (SoundEngine && BoatEngineSound)
		{
			irrklang::ik_f32 volume = BoatEngineSound->getVolume();
			if(volume == 0.0f)
				BoatEngineSound->setIsPaused(false);
			volume += 0.5f * deltaTime;
			volume *= 1.2f;
			volume = min(volume, 0.35f);
			BoatEngineSound->setVolume(volume);
		}
	}
	else
	{
		// Stop engine
		if (SoundEngine && BoatEngineSound)
		{
			irrklang::ik_f32 volume = BoatEngineSound->getVolume();
			
			volume -= 1.f * deltaTime;
			volume = max(volume, 0.0f);
			BoatEngineSound->setVolume(volume);
			if (volume == 0.0f)
				BoatEngineSound->setIsPaused(true);
		}
	}

	boat_.setMovement(movement);

	// Quit when user presses escape
	// might need to change value in config
	if (iFramework.getInputManager().isRepeat("quit"))
	{
		iFramework.shouldClose();
	}
}

void MyAmazingGame::update(double deltaTime)
{
	for (GameObject* obj : GameObject::Objects)
	{
		obj->update((float)deltaTime);
		obj->updateCamera(camera_, (float)deltaTime);
	}
}

void MyAmazingGame::render()
{
	glClearColor(color.r, color.g, color.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	// wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// enable gamma correction
	glEnable(GL_FRAMEBUFFER_SRGB);

	water_.render(camera_, (float)timeElapsed);
	boat_.render(camera_, (float)timeElapsed);

	glDisable(GL_DEPTH_TEST);

	GLenum error = glGetError();
	if (error) std::cout << error << "\n";
}
