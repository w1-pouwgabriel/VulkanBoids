#include "Graphics.h"
#include "Instance.h"
#include "Logging.h"
#include "Device.h"

Graphics::Graphics()
{
	if (debugMode) {
		std::cout << "Making a graphics engine\n";
	}

	CreateGLFW();
	CreateInstance();
	CreateDevice();
}

void Graphics::CreateGLFW()
{
	//initialize glfw
	glfwInit();

	//no default rendering client, we'll hook vulkan up
	//to the window later
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	//resizing breaks the swapchain, we'll disable it for now
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	//GLFWwindow* glfwCreateWindow (int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share)
	if (window = glfwCreateWindow(windowWidth, windowHeight, "WindowGLFW", nullptr, nullptr)) {
		if (debugMode) {
			std::cout << "Successfully made a glfw window, width: " << windowWidth << ", height: " << windowHeight << '\n';
		}
	}
	else {
		if (debugMode) {
			std::cout << "GLFW window creation failed\n";
		}
	}
}

void Graphics::CreateInstance()
{
	instance = VkInit::MakeInstance(debugMode, "graphics");
	dispatchLoaderD = vk::DispatchLoaderDynamic(instance, vkGetInstanceProcAddr);

	if (debugMode) {
		debugMessenger = VkInit::MakeDebugMessenger(instance, dispatchLoaderD);
	}
	
	if (glfwCreateWindowSurface(instance, window, nullptr, (VkSurfaceKHR*)&surface) == VK_SUCCESS) {
		if (debugMode) {
			std::cout << "Succesfully created the gltf window \n";
		}
	}
	else {
		if (debugMode) {
			std::cout << "Could not create a gltf window \n";
		}
	}
}

void Graphics::CreateDevice()
{
	physicalDevice = VkInit::MakePhysicalDevice(instance, debugMode);
	logicalDevice = VkInit::MakeLogicalDevice(physicalDevice, surface, debugMode);
	auto familyQueues = VkInit::GetQueues(physicalDevice, logicalDevice, surface, debugMode);
	graphicsQueue = familyQueues[0];
	presentQueue = familyQueues[1];


}

Graphics::~Graphics()
{
	logicalDevice.destroy();

	instance.destroySurfaceKHR(surface);

	//Unload
	if (debugMode) {
		instance.destroyDebugUtilsMessengerEXT(debugMessenger, nullptr, dispatchLoaderD);
	}

	instance.destroy();

	glfwDestroyWindow(window);
	glfwTerminate();
}