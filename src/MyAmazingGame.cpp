#include "MyAmazingGame.h"



void MyAmazingGame::preInit( sf::Framework< MyAmazingGame >& iFramework )
{
	iFramework.getTextureManager().registerTextureLoader< sf::TGATextureLoader >( "tga" );

	gameObject = new GameObject();
}

void MyAmazingGame::postInit( sf::Framework< MyAmazingGame >& iFramework )
{
	ourShader_ = Shader("asset/shaders/water_simple.vs", "asset/shaders/water_simple.fs");

	gameObject->setData();

	ourShader_.use();
}

void MyAmazingGame::step( sf::Framework< MyAmazingGame >& iFramework, double deltaTime)
{
	const glm::vec2 windowSize = glm::vec2(iFramework.getWindow().getWindowWidth(), iFramework.getWindow().getWindowHeight());
	const glm::float32 aspectRatio = windowSize.x / windowSize.y;

	processInput(iFramework, deltaTime);

	glClearColor(color.r, color.g, color.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	// wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// enable gamma correction
	glEnable(GL_FRAMEBUFFER_SRGB);

	// activate shader
	ourShader_.use();


	// pass projection matrix to shader (note that in this case it could change every frame)
	glm::mat4 projection = glm::perspective(glm::radians(camera_.Zoom), aspectRatio, NEAR_PLANE, FAR_PLANE);
	ourShader_.setMat4("projection", projection);


	// camera/view transformation
	glm::mat4 view = glm::mat4(1.0f);
	view = camera_.GetViewMatrix(true);
	ourShader_.setMat4("view", view);


	// calculate the model matrix for each object and pass it to shader before drawing
	 // make sure to initialize matrix to identity matrix first
	glm::mat4 model = gameObject->getModelMatrix();
	ourShader_.setMat4("model", model);

	ourShader_.setVec3("viewPos", camera_.Position);

	ourShader_.setFloat("time", (float)timeElapsed);

	gameObject->render();

	glDisable(GL_DEPTH_TEST);

	timeElapsed += deltaTime;
	//std::cout << "Time elapsed: " << timeElapsed << "\n";
	GLenum error = glGetError();
	if (error) std::cout << error << "\n";
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
	if (glm::length(movement) > 0.0f)
		movement = glm::normalize(movement);

	gameObject->setMovement(movement);
	gameObject->update((float)deltaTime);
	static bool b = false;
	if(!b)
	gameObject->updateCamera(camera_,(float)deltaTime);
	b = true;


	if (iFramework.getInputManager().isRepeat("quit"))
	{
		iFramework.shouldClose();
	}
}