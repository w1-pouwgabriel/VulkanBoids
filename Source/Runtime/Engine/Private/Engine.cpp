#include "Engine.h"

Engine::Engine()
{
	graphics = new GraphicsApp(640, 480);
}

Engine::~Engine()
{
	delete graphics;
}
