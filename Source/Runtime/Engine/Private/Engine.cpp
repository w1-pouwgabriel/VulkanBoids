#include "Engine.h"

Engine::Engine() :
	scene()
{
	graphics = new App(640, 480);
}

void Engine::Run()
{
	graphics->Run(scene);
}

Engine::~Engine()
{
	delete graphics;
}
