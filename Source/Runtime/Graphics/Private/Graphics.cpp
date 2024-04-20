#include "Graphics.h"
#include "Instance.h"
#include "Logging.h"
#include "Device.h"
#include "Swapchain.h"
#include "Pipeline.h"
#include "Framebuffer.h"
#include "Commands.h"
#include "Sync.h"

Graphics::Graphics(int width, int height, GLFWwindow *window)
{
	windowWidth = width;
	windowHeight = height;
	this->window = window;

	CreateInstance();
	CreateDevice();
	CreatePipeline();
	FinalizeSetup();
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

	VkInit::SwapChainBundle bundle = VkInit::CreateSwapchain(logicalDevice, physicalDevice, surface, windowWidth, windowHeight);
	swapchain = bundle.swapchain;
	swapchainFrames = bundle.frames;
	swapchainFormat = bundle.format;
	swapchainExtent = bundle.extent;
}

void Graphics::CreatePipeline()
{
	VkInit::GraphicsPipelineInBundle specs = {};
	specs.device = logicalDevice;
	specs.vertexFilepath = "Shaders/vertex.spv";
	specs.fragmentFilepath = "Shaders/fragment.spv";
	specs.swapchainExtent = swapchainExtent;
	specs.swapchainImageFormat = swapchainFormat;

	VkInit::GraphicsPipelineOutBundle output = VkInit::CreateGraphicsPipeline(specs);
	layout = output.layout;
	renderpass = output.renderpass;
	pipeline = output.pipeline;
}

void Graphics::FinalizeSetup()
{
	VkInit::framebufferInput frameBufferInput;
	frameBufferInput.device = logicalDevice;
	frameBufferInput.renderpass = renderpass;
	frameBufferInput.swapchainExtent = swapchainExtent;
	VkInit::CreateFramebuffers(frameBufferInput, swapchainFrames);

	
}

Graphics::~Graphics()
{
	logicalDevice.destroyRenderPass(renderpass);

	logicalDevice.destroyPipelineLayout(layout);

	logicalDevice.destroyPipeline(pipeline);

	for (size_t i = 0; i < swapchainFrames.size(); i++)
	{
		logicalDevice.destroyImageView(swapchainFrames[i].imageView);
		logicalDevice.destroyFramebuffer(swapchainFrames[i].frameBuffer);
	}

	logicalDevice.destroySwapchainKHR(swapchain);

	logicalDevice.destroy();

	instance.destroySurfaceKHR(surface);

	//Unload
	#if ENABLE_VALIDATION_LAYER
		instance.destroyDebugUtilsMessengerEXT(debugMessenger, nullptr, dispatchLoaderD);
	#endif

	instance.destroy();
}