#include "Swapchain.h"
#include "Logging.h"
#include <string>

namespace VkInit
{
    SwapChainSupportDetails QuerySwapChainSupport(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface)
    {
        SwapChainSupportDetails support;
        support.capabilities = device.getSurfaceCapabilitiesKHR(surface);
        /**
        typedef struct VkSurfaceCapabilitiesKHR {
            uint32_t                         minImageCount;
            uint32_t                         maxImageCount;
            VkExtent2D                       currentExtent;
            VkExtent2D                       minImageExtent;
            VkExtent2D                       maxImageExtent;
            uint32_t                         maxImageArrayLayers;
            VkSurfaceTransformFlagsKHR       supportedTransforms;
            VkSurfaceTransformFlagBitsKHR    currentTransform;
            VkCompositeAlphaFlagsKHR         supportedCompositeAlpha;
            VkImageUsageFlags                supportedUsageFlags;
        } VkSurfaceCapabilitiesKHR;
        */

#if ENABLE_VALIDATION_LAYER
        std::cout << "Swapchain support details: \n";
        std::cout << "\t minImageCount: " << support.capabilities.minImageCount << "\n";
        std::cout << "\t maxImageCount: " << support.capabilities.maxImageCount << "\n";
        //These extensts are based on the gltf window size
        std::cout << "\t currentExtent: { " << support.capabilities.currentExtent.width << " , " << support.capabilities.currentExtent.height << " }" << "\n";
        std::cout << "\t minImageExtent: { " << support.capabilities.minImageExtent.width << " , " << support.capabilities.minImageExtent.height << " }" << "\n";
        std::cout << "\t maxImageExtent: { " << support.capabilities.maxImageExtent.width << " , " << support.capabilities.maxImageExtent.height << " }" << "\n";
        //-----------------------------------------------
        std::cout << "\t maxImageArrayLayers: " << support.capabilities.maxImageArrayLayers << "\n";

        std::cout << "\tsupported transforms:\n";
        std::vector<std::string> stringList = LogTransformBits(support.capabilities.supportedTransforms);
        for (std::string line : stringList) {
            std::cout << "\t\t" << line << '\n';
        }

        std::cout << "\tcurrent transform:\n";
        stringList = LogTransformBits(support.capabilities.currentTransform);
        for (std::string line : stringList) {
            std::cout << "\t\t" << line << '\n';
        }

        std::cout << "\tsupported alpha operations:\n";
        stringList = LogAlphaCompositeBits(support.capabilities.supportedCompositeAlpha);
        for (std::string line : stringList) {
            std::cout << "\t\t" << line << '\n';
        }

        std::cout << "\tsupported image usage:\n";
        stringList = LogImageUsageBits(support.capabilities.supportedUsageFlags);
        for (std::string line : stringList) {
            std::cout << "\t\t" << line << '\n';
        }
#endif

        support.formats = device.getSurfaceFormatsKHR(surface);

#if ENABLE_VALIDATION_LAYER  
        for (auto supportedFormat : support.formats) {
            std::cout << "Supported pixel format: " << vk::to_string(supportedFormat.format) << "\n";
            std::cout << "Supported color spaces: " << vk::to_string(supportedFormat.colorSpace) << "\n";
        }
#endif

        support.presentModes;

        return support;
    }
}