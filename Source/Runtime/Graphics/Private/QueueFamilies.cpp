#include "QueueFamilies.h"

namespace VkUtil{
    QueueFamilyIndices findQueueFamilies(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface)
    {
        QueueFamilyIndices indices;

        std::vector<vk::QueueFamilyProperties> queueFamilyProperties = device.getQueueFamilyProperties();

        #if ENABLE_VALIDATION_LAYER
            std::cout << "Supports " << queueFamilyProperties.size() << " different queue families\n";
        #endif

        int i = 0;
        for (vk::QueueFamilyProperties queueFam : queueFamilyProperties)
        {
            /*
            // Provided by VK_VERSION_1_0
            typedef enum VkQueueFlagBits {
                VK_QUEUE_GRAPHICS_BIT = 0x00000001,
                VK_QUEUE_COMPUTE_BIT = 0x00000002,
                VK_QUEUE_TRANSFER_BIT = 0x00000004,
                VK_QUEUE_SPARSE_BINDING_BIT = 0x00000008,
                VK_QUEUE_PROTECTED_BIT = 0x00000010,
                VK_QUEUE_VIDEO_DECODE_BIT_KHR = 0x00000020,
                VK_QUEUE_VIDEO_ENCODE_BIT_KHR = 0x00000040,
                VK_QUEUE_OPTICAL_FLOW_BIT_NV = 0x00000100,
            } VkQueueFlagBits;
            */

            if (queueFam.queueFlags & vk::QueueFlagBits::eGraphics) {
                indices.graphicsFamily = i;

                #if ENABLE_VALIDATION_LAYER
                    std::cout << "Queue family " << i << " is chosen for graphics\n";
                    std::cout << "This family supports " << queueFam.queueCount << " queues\n";
                #endif
            }
            if (device.getSurfaceSupportKHR(i, surface)) {
                indices.presentFamily = i;

                #if ENABLE_VALIDATION_LAYER
                    std::cout << "Queue family " << i << " is chosen for presenting\n";
                #endif
            }

            //If we were able to find all the queues that we need, break
            if (indices.isComplete()) {
                break;
            }

            i++;
        }

        return indices;
    }
}