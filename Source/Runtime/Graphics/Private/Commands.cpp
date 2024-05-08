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

    vk::CommandBuffer CreateCommandBuffers(commandBufferInputChunk inputChunk)
    {
		vk::CommandBufferAllocateInfo allocInfo = {};
		allocInfo.commandPool = inputChunk.commandPool;
		allocInfo.level = vk::CommandBufferLevel::ePrimary;
		allocInfo.commandBufferCount = 1;

		//Make a command buffer for each frame
		for (int i = 0; i < inputChunk.frames.size(); ++i) {
			try {
				inputChunk.frames[i].commandBuffer = inputChunk.device.allocateCommandBuffers(allocInfo)[0];
				
				#ifdef ENABLE_VALIDATION_LAYER
					std::cout << "Allocated command buffer for frame " << i << std::endl;
				#endif
			}
			catch (vk::SystemError err) {

				#ifdef ENABLE_VALIDATION_lAYER
					std::cout << "Failed to allocate command buffer for frame " << i << std::endl;
				#endif
			}
		}

		//Make a "main" command buffer for the engine
		try {
			vk::CommandBuffer commandBuffer = inputChunk.device.allocateCommandBuffers(allocInfo)[0];

			#ifdef ENABLE_VALIDATION_lAYER
				std::cout << "Allocated main command buffer " << std::endl;
			#endif

			return commandBuffer;
		}
		catch (vk::SystemError err) {

			#ifdef ENABLE_VALIDATION_lAYER
				std::cout << "Failed to allocate main command buffer " << std::endl;
			#endif

			return nullptr;
		}
    }
}