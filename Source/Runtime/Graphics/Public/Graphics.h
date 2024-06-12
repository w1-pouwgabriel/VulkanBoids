#pragma once
#include "Utils.h"
#include "Frame.h"

#include "Scene.h"

class Graphics
{
public:
	Graphics(int width, int height, GLFWwindow* window);
	~Graphics();

	void Render(Scene& scene);
	void RecreateSwapchain();

private:
	//GLFW
	int windowWidth;
	int windowHeight;
	GLFWwindow* window;

	//Vulkan
	//	Instance
	vk::Instance instance{ nullptr };
	vk::DebugUtilsMessengerEXT debugMessenger{ nullptr };
	//	Dispatch loader to load functions at run-time
	vk::DispatchLoaderDynamic dispatchLoaderD;
	vk::SurfaceKHR surface;
	void CreateInstance();

	//	Device
	vk::PhysicalDevice physicalDevice;
	vk::Device logicalDevice;
	vk::Queue graphicsQueue;
	vk::Queue presentQueue;
	vk::SwapchainKHR swapchain{ nullptr };
	std::vector<VkUtil::SwapChainFrame> swapchainFrames;
	vk::Format swapchainFormat;
	vk::Extent2D swapchainExtent;
	void CreateDevice();

	//Pipeline
	vk::PipelineLayout layout;
	vk::RenderPass renderpass;
	vk::Pipeline pipeline;
	void CreatePipeline();
	void CleanupSwapchain();

	//Command-related variables
	vk::CommandPool commandPool;
	vk::CommandBuffer mainCommandBuffer;
	void CreateFramebuffers();

	//Synchronization objects
	int maxFramesInFlight, frameNumber;
	void CreateSyncObjects();

	void FinalizeSetup();

	//Draw command buffers
	void DrawCommandbuffer(vk::CommandBuffer commandBuffer, int32_t imageIndex, Scene& scene);
};