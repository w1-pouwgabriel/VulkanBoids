#pragma once
#include "Utils.h"

namespace VkUtil{
    
	struct SwapChainFrame{
		vk::Image image;
		vk::ImageView imageView;
	};
	
}