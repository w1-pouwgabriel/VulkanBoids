#include "Engine.h"
#include "Graphics.h"

Engine::Engine()
{
	theGraphics = new Graphics();
}

Engine::~Engine()
{
	delete theGraphics;
}
