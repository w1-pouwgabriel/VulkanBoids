#pragma once
#include "Utils.h"

namespace VkUtil{
    /**
		Store all the image information
	*/
	struct SwapChainFrame{
		vk::Image image;
		vk::ImageView imageView;
		vk::Framebuffer frameBuffer;
		vk::CommandBuffer commandBuffer;
		//Synchronization objects
		vk::Fence inFlight;
		vk::Semaphore imageAvailable, renderFinished;
	};
	
}