#pragma once

#include "App.h"

class Engine
{
public:
	Engine();
	~Engine();

	void Run();

private:
	App* graphics;
};