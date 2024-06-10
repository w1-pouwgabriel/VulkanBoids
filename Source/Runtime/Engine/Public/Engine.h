#pragma once

#include <memory>

class App;
class Scene;

class Engine
{
public:
	Engine();
	~Engine();

	void Run();

private:
	std::unique_ptr<App> graphics;
	std::shared_ptr<Scene> scene;
};