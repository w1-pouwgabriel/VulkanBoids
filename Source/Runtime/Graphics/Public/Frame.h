#pragma once
#include "Utils.h"

namespace VkUtil{
    /**
		Store all the image information in 1 place
	*/
	struct SwapChainFrame{
		vk::Image image;
		vk::ImageView imageView;
		vk::Framebuffer frameBuffer;
		vk::CommandBuffer commandBuffer;
	};
	
}