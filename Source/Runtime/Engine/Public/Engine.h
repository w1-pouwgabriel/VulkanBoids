#pragma once

#include "App.h"
#include "Scene.h"

#include <memory>

class Engine
{
public:
	Engine();
	~Engine();

	void Run();

private:
	App* graphics;
	Scene scene;
};