#pragma once
#include "Utils.h"
#include "Graphics.h"

class GraphicsApp {
public:
	GraphicsApp(int width, int height);
	~GraphicsApp();
	
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