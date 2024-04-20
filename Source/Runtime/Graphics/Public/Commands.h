#pragma once
#include "Utils.h"
#include "Frame.h"

namespace VkInit 
{
	/**
		Data structures used in creating command buffers
	*/
	struct commandBufferInputChunk {
		vk::Device device; 
		vk::CommandPool commandPool;
		std::vector<VkUtil::SwapChainFrame>& frames;
	};


	/**
		Make a command pool.

		\param logicalDevice the logical device
		\param physicalDevice the physical device
		\param surface the windows surface (used for getting the queue families)
		\returns the created command pool
	*/
	vk::CommandPool CreateCommandPool(
        vk::Device logicalDevice, 
        vk::PhysicalDevice physicalDevice, 
        vk::SurfaceKHR surface  
    );
}
