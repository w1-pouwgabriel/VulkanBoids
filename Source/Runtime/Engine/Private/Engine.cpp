#include "Engine.h"

#include "GraphicsApp.h"
#include "Scene.h"

Engine::Engine()
	: scene(), graphics(640, 480)
{

}

void Engine::Run()
{
	graphics.Run(scene);
}

Engine::~Engine()
{

}
