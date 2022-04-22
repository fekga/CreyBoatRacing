#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "rapidjson/document.h"


//#include <stb_image.h>

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>

#include "debug.h"
#include "Types.h"
#include "static_string.h"
#include "Utils.h"
#include "Window.h"
#include "Texture.cpp"
#include "Sprite.cpp"
#include "TextureLoaderBase.cpp"
#include "TGATextureLoader.cpp"
#include "TextureManager.cpp"
#include "InputManager.cpp"
#include "Framework.cpp"

#include "MyAmazingGame.cpp"



int main( void )
{
	sf::Framework< MyAmazingGame > framework = {};
	const bool ret = framework.init();
	if ( !ret )
	{
		framework.terminate();
		return -1;
	}
	framework.loop();
	framework.terminate();
	return 0;
}