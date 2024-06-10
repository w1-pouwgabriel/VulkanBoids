#pragma once
#include "Utils.h"
#include "Graphics.h"

class App {
public:
	App(int width = 640, int height = 480);
	~App();
	
	void Run(std::shared_ptr<Scene> scene);

private:
	Graphics* graphicsEngine;
	GLFWwindow* window;

	double lastTime, currentTime;
	int numFrames;
	float frameTime;

	void CreateGLFW(int width, int height);

	void CalculateFrameRate();
};