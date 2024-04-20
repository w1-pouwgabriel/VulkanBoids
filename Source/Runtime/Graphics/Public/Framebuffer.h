#pragma once
#include "Utils.h"
#include "Frame.h"

namespace VkInit{

    /**
		Data structures involved in making framebuffers for the
		swapchain.
	*/
	struct framebufferInput {
		vk::Device device;
		vk::RenderPass renderpass;
		vk::Extent2D swapchainExtent;
	};

    /**
		Make framebuffers for the swapchain

		\param inputChunk required input for creation
		\param frames the vector to be populated with the created framebuffers
	*/
    void CreateFramebuffers(framebufferInput inputChunk, std::vector<VkUtil::SwapChainFrame>& frames);
}