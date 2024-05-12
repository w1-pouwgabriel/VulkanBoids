#include "Graphics.h"
#include "Instance.h"
#include "Logging.h"
#include "Device.h"
#include "Swapchain.h"
#include "Pipeline.h"
#include "Framebuffer.h"
#include "Commands.h"
#include "Sync.h"
#include "Scene.h"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

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
	maxFramesInFlight = static_cast<int>(swapchainFrames.size());
	frameNumber = 0;
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
	
	commandPool = VkInit::CreateCommandPool(logicalDevice, physicalDevice, surface);

	VkInit::commandBufferInputChunk commandBufferInput = {logicalDevice, commandPool, swapchainFrames};
	mainCommandBuffer = VkInit::CreateCommandBuffers(commandBufferInput); 

	for (auto &frame : swapchainFrames)
	{
		frame.inFlight = VkInit::CreateFence(logicalDevice);
		frame.imageAvailable  = VkInit::CreateSemaphore(logicalDevice);
		frame.renderFinished = VkInit::CreateSemaphore(logicalDevice);
	}
}

void Graphics::DrawCommandbuffer(vk::CommandBuffer commandBuffer, int32_t imageIndex, Scene& scene) 
{
	vk::CommandBufferBeginInfo beginInfo = {};

	try {
		commandBuffer.begin(beginInfo);
	}
	catch (vk::SystemError err) {
		#if ENABLE_VALIDATION_LAYER
			std::cout << "Failed to begin recording command buffer!" << std::endl;
		#endif
	}

	vk::RenderPassBeginInfo renderPassInfo = {};
	renderPassInfo.renderPass = renderpass;
	renderPassInfo.framebuffer = swapchainFrames[imageIndex].frameBuffer;
	renderPassInfo.renderArea.offset.x = 0;
	renderPassInfo.renderArea.offset.y = 0;
	renderPassInfo.renderArea.extent = swapchainExtent;

	vk::ClearValue clearColor = { std::array<float, 4>{1.0f, 0.5f, 0.25f, 1.0f} };
	renderPassInfo.clearValueCount = 1;
	renderPassInfo.pClearValues = &clearColor;

	commandBuffer.beginRenderPass(&renderPassInfo, vk::SubpassContents::eInline);

	commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline);

	for (glm::vec3 position : scene.trianglePositions) {

		glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
		VkUtil::ObjectData objectData;
		objectData.model = model;
		commandBuffer.pushConstants(
			layout, vk::ShaderStageFlagBits::eVertex,
			0, sizeof(objectData), &objectData
		);

		commandBuffer.draw(3, 1, 0, 0);

	}

	commandBuffer.endRenderPass();

	try {
		commandBuffer.end();
	}
	catch (vk::SystemError err) {
		#if ENABLE_VALIDATION_LAYER
			std::cout << "failed to record command buffer!" << std::endl;
		#endif
	}
}

void Graphics::Render(Scene& scene)
{
	logicalDevice.waitForFences(1, &swapchainFrames[frameNumber].inFlight, VK_TRUE, UINT64_MAX);
	logicalDevice.resetFences(1, &swapchainFrames[frameNumber].inFlight);
	
	//acquireNextImageKHR(vk::SwapChainKHR, timeout, semaphore_to_signal, fence)
	uint32_t imageIndex{ logicalDevice.acquireNextImageKHR(swapchain, UINT64_MAX, swapchainFrames[frameNumber].imageAvailable, nullptr).value };

	vk::CommandBuffer commandBuffer = swapchainFrames[imageIndex].commandBuffer;

	commandBuffer.reset();

	// for (Models &model : moddels)
	// {
	// 		DrawCommandbuffer(model.commandBuffer, imageIndex);
	// }

	DrawCommandbuffer(commandBuffer, imageIndex, scene);

	vk::SubmitInfo submitInfo = {};

	vk::Semaphore waitSemaphores[] = { swapchainFrames[frameNumber].imageAvailable };
	vk::PipelineStageFlags waitStages[] = { vk::PipelineStageFlagBits::eColorAttachmentOutput };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	vk::Semaphore signalSemaphores[] = { swapchainFrames[frameNumber].renderFinished };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	try {
		graphicsQueue.submit(submitInfo, swapchainFrames[frameNumber].inFlight);
	}
	catch (vk::SystemError err) {
		#if ENABLE_VALIDATION_LAYER
			std::cout << "failed to submit draw command buffer!" << std::endl;
		#endif
	}

	vk::PresentInfoKHR presentInfo = {};
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	vk::SwapchainKHR swapChains[] = { swapchain }; 
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;

	presentInfo.pImageIndices = &imageIndex;

	presentQueue.presentKHR(presentInfo);

	frameNumber = (frameNumber + 1) % maxFramesInFlight;
}

Graphics::~Graphics()
{
	logicalDevice.waitIdle();

	logicalDevice.destroyCommandPool(commandPool);

	logicalDevice.destroyRenderPass(renderpass);

	for (auto frame : swapchainFrames)
	{
		logicalDevice.destroyFence(frame.inFlight);
		logicalDevice.destroySemaphore(frame.imageAvailable);
		logicalDevice.destroySemaphore(frame.renderFinished);
		logicalDevice.destroyImageView(frame.imageView);
		logicalDevice.destroyFramebuffer(frame.frameBuffer);
	}

	logicalDevice.destroyPipelineLayout(layout);

	logicalDevice.destroyPipeline(pipeline);

	logicalDevice.destroySwapchainKHR(swapchain);

	logicalDevice.destroy();

	instance.destroySurfaceKHR(surface);

	//Unload
	#if ENABLE_VALIDATION_LAYER
		instance.destroyDebugUtilsMessengerEXT(debugMessenger, nullptr, dispatchLoaderD);
	#endif

	instance.destroy();
}