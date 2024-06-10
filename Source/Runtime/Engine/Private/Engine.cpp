#include "Engine.h"
#include "App.h"
#include "Scene.h"

Engine::Engine() :
	graphics()
{
	scene = std::shared_ptr<Scene>();
}

void Engine::Run()
{
	graphics->Run(scene);
}

Engine::~Engine()
{}
