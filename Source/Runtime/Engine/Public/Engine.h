#pragma once

#include "GraphicsApp.h"
#include "Scene.h"
#include <memory>

struct foo{
	int i = 1;
};

class Engine
{
public:
	Engine();
	~Engine();

	void Run();

private:
	GraphicsApp graphics;
	Scene scene;
};