#include "QueueFamilies.h"
#include "Commands.h"

namespace VkInit 
{
    vk::CommandPool CreateCommandPool(vk::Device logicalDevice, vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface)
    {
        VkUtil::QueueFamilyIndices queueFamilyIndices = VkUtil::findQueueFamilies(physicalDevice, surface);

		vk::CommandPoolCreateInfo poolInfo;
		poolInfo.flags = vk::CommandPoolCreateFlags() | vk::CommandPoolCreateFlagBits::eResetCommandBuffer;
		poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

		try {
			return logicalDevice.createCommandPool(poolInfo);
		}
		catch (vk::SystemError err) {
			#ifdef ENABLE_VALIDATION_LAYER
				std::cout << "Failed to create Command Pool" << std::endl;
			#endif
			return nullptr;
		}
    }
}