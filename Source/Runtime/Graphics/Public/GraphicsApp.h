#pragma once
#include "Utils.h"
#include "Graphics.h"

class GraphicsApp {
public:
	GraphicsApp(int width = 640, int height = 480);
	~GraphicsApp();
	
	void Run(Scene& scene);

private:
	Graphics* graphicsEngine;
	GLFWwindow* window;

	double lastTime, currentTime;
	int numFrames;
	float frameTime;

	void CreateGLFW(int width, int height);

	void CalculateFrameRate();
};