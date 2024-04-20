#include "GraphicsApp.h"

GraphicsApp::GraphicsApp(int width, int height)
{
    CreateGLFW(width, height);

    graphicsEngine = new Graphics(width, height, window);
}

GraphicsApp::~GraphicsApp()
{
	delete graphicsEngine;

	glfwDestroyWindow(window);
	glfwTerminate();
}

void GraphicsApp::CreateGLFW(int width, int height)
{
    //initialize glfw
	glfwInit();

	//no default rendering client, we'll hook vulkan up
	//to the window later
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	//resizing breaks the swapchain, we'll disable it for now
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	//GLFWwindow* glfwCreateWindow (int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share)
	if (window = glfwCreateWindow(width, height, "WindowGLFW", nullptr, nullptr)) {
		#if ENABLE_VALIDATION_LAYER
			std::cout << "Successfully made a glfw window, width: " << width << ", height: " << height << '\n';
		#endif
	}
	else {
		#if ENABLE_VALIDATION_LAYER
			std::cout << "GLFW window creation failed\n";
		#endif
	}
}

void GraphicsApp::CalculateFrameRate()
{

}

void GraphicsApp::Run()
{

}