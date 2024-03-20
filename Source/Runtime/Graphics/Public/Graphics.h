#pragma once

#include "Utils.h"

class Graphics
{
public:
	Graphics();
	~Graphics();

private:
	//Used for validation layers and other debug shit
#ifndef NDEBUG
	bool debugMode = true;
#else
	bool debugMode = false;
#endif

	//GLFW
	int windowWidth{ 640 };
	int windowHeight{ 480 };
	GLFWwindow* window{ nullptr };
	void CreateGLFW();

	//Vulkan
	//	Instance
	vk::Instance instance{ nullptr };
	vk::DebugUtilsMessengerEXT debugMessenger{ nullptr };
	//	Dispatch loader to load functions at run-time
	vk::DispatchLoaderDynamic dispatchLoaderD;
	vk::SurfaceKHR surface;
	void CreateInstance();

	// Device
	vk::PhysicalDevice physicalDevice;
	vk::Device logicalDevice;

	vk::Queue graphicsQueue;
	vk::Queue presentQueue;
	void CreateDevice();
};