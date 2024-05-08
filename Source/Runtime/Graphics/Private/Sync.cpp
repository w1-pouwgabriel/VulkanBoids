#include "Sync.h"

namespace VkInit
{
    vk::Semaphore CreateSemaphore(vk::Device device)
    {
        vk::SemaphoreCreateInfo semaphoreInfo = {};
        semaphoreInfo.flags = vk::SemaphoreCreateFlags();

        try {
            return device.createSemaphore(semaphoreInfo);
        }
        catch (vk::SystemError err) {
            #if ENABLE_VALIDATION_LAYER
                std::cout << "Failed to create semaphore " << std::endl;
            #endif
            return nullptr;
        }
    }

    vk::Fence CreateFence(vk::Device device)
    {
        vk::FenceCreateInfo fenceInfo = {};
        fenceInfo.flags = vk::FenceCreateFlags() | vk::FenceCreateFlagBits::eSignaled;

        try {
            return device.createFence(fenceInfo);
        }
        catch (vk::SystemError err) {
            #if ENABLE_VALIDATION_LAYER
                std::cout << "Failed to create fence " << std::endl;
            #endif
            return nullptr;
        }
    }
}