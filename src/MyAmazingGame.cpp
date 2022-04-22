#include "MyAmazingGame.h"

#include <stb_image.h>

MyAmazingGame::~MyAmazingGame()
{
	if (SoundEngine)
		SoundEngine->drop();

	for (auto& obj : GameObject::Objects)
	{
		obj->is_dead = true;
	}
	removeDead();
	EntityModel::clearModels();
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

		CoinSoundSource = SoundEngine->addSoundSourceFromFile("asset/music/pickupCoin.wav", irrklang::ESM_AUTO_DETECT, true);

		GameWinSoundSource = SoundEngine->addSoundSourceFromFile("asset/music/mixkit-winning-chimes-2015.wav", irrklang::ESM_AUTO_DETECT, true);
	}
}

void MyAmazingGame::postInit( sf::Framework< MyAmazingGame >& iFramework )
{
	// OpenGL is supposed to be set up now, can use openGL functions


	// Set up camera values
	const glm::vec2 windowSize = glm::vec2(iFramework.getWindow().getWindowWidth(), iFramework.getWindow().getWindowHeight());
	const glm::float32 aspectRatio = windowSize.x / windowSize.y;

	// Hide mouse cursor
	glfwSetInputMode(iFramework.getWindow().getGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	camera_.AspectRatio = aspectRatio;

	GameObject::SunPosition = glm::vec3(0.0f, 1500.0f, -500.0f);
	
	// Wave
	// xy = direction (will be normalized)
	// z = steepness
	// w = wavelength
	// steepness values should sum to 1

	float steepness = 1.0f / 3.0f;
	const glm::vec4 WaveA = glm::vec4(1, 1, steepness, 40);
	const glm::vec4 WaveB = glm::vec4(1, .6, steepness, 21);
	const glm::vec4 WaveC = glm::vec4(1, 1.3, steepness, 15);
	GameObject::Waves.push_back(WaveA);
	GameObject::Waves.push_back(WaveB);
	GameObject::Waves.push_back(WaveC);

	// tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
	// not required, assimp already flips the image
	//stbi_set_flip_vertically_on_load(true);

	// Add water
	water_ = GameObject::create<Water>();

	// Add boat
	boat_ = GameObject::create<Boat>();


	// Add buoys
	int buoyCount = 36 * 3;
	for (int i = 0; i < buoyCount; ++i)
	{
		auto obj = GameObject::create<Buoy>();
		float angle = float(i) * 2.0f * glm::pi<float>() / float(buoyCount);
		glm::vec2 euc = glm::vec2(glm::cos(angle), glm::sin(angle)) * 500.0f;
		obj->setPosition(glm::vec3(euc.y, 0.0f, euc.x));
		buoys.push_back(obj);
	}

	// Add buoys
	int coinCount = 10 * 1;
	for (int i = 0; i < coinCount; ++i)
	{
		auto obj = GameObject::create<Coin>();
		glm::vec2 pos = glm::diskRand(400.0f);
		obj->setPosition(glm::vec3(pos.x, 0.0f, pos.y));
		coins.push_back(obj);
	}

	// Initialize objects' data
	for (auto &obj : GameObject::Objects)
	{
		obj->init();
	}
}

void MyAmazingGame::step(sf::Framework< MyAmazingGame >& iFramework, double deltaTime)
{
	
	processInput(iFramework, deltaTime);
	update(deltaTime);
	collisionDetection();
	removeDead();
	logic();
	render();

	timeElapsed += deltaTime;
	GameObject::ElapsedTime = (float)timeElapsed;
}

void MyAmazingGame::processInput(sf::Framework< MyAmazingGame >& iFramework, double deltaTime)
{
	const glm::vec2 windowSize = glm::vec2(iFramework.getWindow().getWindowWidth(), iFramework.getWindow().getWindowHeight());
	const glm::vec2 mousePos = iFramework.getInputManager().getMousePos();
	glm::vec2 normalizedMousePos = (glm::float32(2.) * mousePos - windowSize) / glm::max(windowSize.x,windowSize.y);


	glm::vec3 movement = glm::vec3(0.0f);
	if (iFramework.getInputManager().isRepeat("up"))
	{
		movement.z += 1.0f;
	}
	//FIXME moving backwards is buggy
	//if (iFramework.getInputManager().isRepeat("down"))
	//{
	//	movement.z -= 1.0f;
	//}
	if (iFramework.getInputManager().isRepeat("left"))
	{
		movement.x += 1.0f;
	}
	if (iFramework.getInputManager().isRepeat("right"))
	{
		movement.x -= 1.0f;
	}

	//TODO move this to Boat
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
			volume += 0.5f * (float)deltaTime;
			volume *= 1.2f;
			volume = glm::min(volume, 0.35f);
			BoatEngineSound->setVolume(volume);
		}
	}
	else
	{
		// Stop engine
		if (SoundEngine && BoatEngineSound)
		{
			irrklang::ik_f32 volume = BoatEngineSound->getVolume();
			
			volume -= 1.f * (float)deltaTime;
			volume = glm::max(volume, 0.0f);
			BoatEngineSound->setVolume(volume);
			if (volume == 0.0f)
				BoatEngineSound->setIsPaused(true);
		}
	}
	boat_->setMovement(movement);

	// Quit when user presses escape
	// might need to change value in config
	if (iFramework.getInputManager().isRepeat("quit"))
	{
		iFramework.shouldClose();
	}
}

void MyAmazingGame::update(double deltaTime)
{
	for (auto &obj : GameObject::Objects)
	{
		obj->update((float)deltaTime);
		obj->updateCamera(camera_, (float)deltaTime);
	}
}

void MyAmazingGame::collisionDetection()
{
	//TODO better collision detection, now it's just simple distance comparison
	const glm::vec3 planeMaskXZ = glm::vec3(1, 0, 1);
	for (auto & obj : coins)
	{
		if (glm::distance(boat_->getPosition()* planeMaskXZ, obj->getPosition()* planeMaskXZ) < 5.0f )
		{
			if(SoundEngine && CoinSoundSource)
				CoinSound = SoundEngine->play2D(CoinSoundSource, false, false, false, true);
			obj->is_dead = true;
		}
	}
}

void MyAmazingGame::removeDead()
{

	//TODO ugly as hell, create better ownership instead of dangling raw pointers
	GameObject::Objects.erase(std::remove_if(GameObject::Objects.begin(), GameObject::Objects.end(),
		[](const auto& p) 
		{ 
			bool dead = false;
			if (p && p->is_dead)
			{
				dead = p->is_dead;
				delete p;
			}
			return dead;
		}
	), GameObject::Objects.end());
	buoys.remove_if(
		[](const auto& p) { return !p || p->is_dead; }
	);
	coins.remove_if(
		[](const auto& p) { return !p || p->is_dead; }
	);
}

void MyAmazingGame::logic()
{
	if (coins.size() == 0 && !gameWon)
	{
		if (SoundEngine && GameWinSoundSource)
			GameWinSound = SoundEngine->play2D(GameWinSoundSource, false, false, false, true);
		gameWon = true;
		// Game won!
		//TODO you can still keep playing though...
		std::cout << "You won!\nPress Escape to quit game\n";
	}
}

void MyAmazingGame::render()
{
	glClearColor(color.r, color.g, color.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	// wireframe mode for debug
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// enable gamma correction
	glEnable(GL_FRAMEBUFFER_SRGB);

	water_->render(camera_, (float)timeElapsed);
	boat_->render(camera_, (float)timeElapsed);
	for (auto & obj : buoys)
	{
		if(obj && !obj->is_dead)
			obj->render(camera_, (float)timeElapsed);
	}
	for (auto & obj : coins)
	{
		if (obj && !obj->is_dead)
			obj->render(camera_, (float)timeElapsed);
	}

	glDisable(GL_DEPTH_TEST);

	GLenum error = glGetError();
	if (error) std::cout << error << "\n";
}
