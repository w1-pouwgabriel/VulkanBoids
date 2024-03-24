#include "Graphics.h"
#include "Instance.h"
#include "Logging.h"
#include "Device.h"
#include "Swapchain.h"

Graphics::Graphics()
{
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
		#if ENABLE_VALIDATION_LAYER
			std::cout << "Successfully made a glfw window, width: " << windowWidth << ", height: " << windowHeight << '\n';
		#endif
	}
	else {
		#if ENABLE_VALIDATION_LAYER
			std::cout << "GLFW window creation failed\n";
		#endif
	}
}

void Graphics::CreateInstance()
{
	instance = VkInit::MakeInstance("graphics");
	dispatchLoaderD = vk::DispatchLoaderDynamic(instance, vkGetInstanceProcAddr);

	#if ENABLE_VALIDATION_LAYER
		debugMessenger = VkInit::MakeDebugMessenger(instance, dispatchLoaderD);
	#endif
	
	if (glfwCreateWindowSurface(instance, window, nullptr, (VkSurfaceKHR*)&surface) == VK_SUCCESS) {
		#if ENABLE_VALIDATION_LAYER
			std::cout << "Succesfully created the gltf window \n";
		#endif
	}
	else {
		#if ENABLE_VALIDATION_LAYER
			std::cout << "Could not create a gltf window \n";
		#endif
	}
}

void Graphics::CreateDevice()
{
	physicalDevice = VkInit::MakePhysicalDevice(instance);
	logicalDevice = VkInit::MakeLogicalDevice(physicalDevice, surface);
	auto familyQueues = VkInit::GetQueues(physicalDevice, logicalDevice, surface);
	graphicsQueue = familyQueues[0];
	presentQueue = familyQueues[1];

	VkInit::SwapChainBundle bundle = VkInit::MakeSwapchain(logicalDevice, physicalDevice, surface, windowWidth, windowHeight);
	swapchain = bundle.swapchain;
	swapchainFrames = bundle.frames;
	swapchainFormat = bundle.format;
	swapchainExtent = bundle.extent;
}

Graphics::~Graphics()
{
	for (size_t i = 0; i < swapchainFrames.size(); i++)
	{
		logicalDevice.destroyImageView(swapchainFrames[i].imageView);
	}

	logicalDevice.destroySwapchainKHR(swapchain);

	logicalDevice.destroy();

	instance.destroySurfaceKHR(surface);

	//Unload
	#if ENABLE_VALIDATION_LAYER
		instance.destroyDebugUtilsMessengerEXT(debugMessenger, nullptr, dispatchLoaderD);
	#endif

	instance.destroy();

	glfwDestroyWindow(window);
	glfwTerminate();
}