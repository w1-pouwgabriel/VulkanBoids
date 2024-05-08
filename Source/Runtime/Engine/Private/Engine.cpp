#include "Engine.h"

Engine::Engine()
{
	graphics = new App(640, 480);
}

void Engine::Run()
{
	graphics->Run();
}

Engine::~Engine()
{
	delete graphics;
}
