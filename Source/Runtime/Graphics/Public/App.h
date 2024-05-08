#pragma once
#include "Utils.h"
#include "Graphics.h"

class App {
public:
	App(int width, int height);
	~App();
	
	void Run();

private:
	Graphics* graphicsEngine;
	GLFWwindow* window;

	double lastTime, currentTime;
	int numFrames;
	float frameTime;

	void CreateGLFW(int width, int height);

	void CalculateFrameRate();
};