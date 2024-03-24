#include "Swapchain.h"
#include "Logging.h"
#include "QueueFamilies.h"
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
            for (vk::SurfaceFormatKHR supportedFormat : support.formats) {
                std::cout << "Supported pixel format: " << vk::to_string(supportedFormat.format) << "\n";
                std::cout << "Supported color spaces: " << vk::to_string(supportedFormat.colorSpace) << "\n";
            }
        #endif

        support.presentModes = device.getSurfacePresentModesKHR(surface);
        #if ENABLE_VALIDATION_LAYER
            for(vk::PresentModeKHR presentMode : support.presentModes)  
                std::cout << "\t"  << LogPresentMode(presentMode) << "\n";
        #endif

        return support;
    }

    vk::SurfaceFormatKHR ChooseSwapchainSurfaceFormat(std::vector<vk::SurfaceFormatKHR> formats)
    {
        for (vk::SurfaceFormatKHR format : formats) {
			if (format.format == vk::Format::eB8G8R8A8Unorm
				&& format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
				return format;
			}
		}

		return formats[0];
    }

	vk::PresentModeKHR ChooseSwapchainPresentMode(std::vector<vk::PresentModeKHR> presentModes) {
		
		for (vk::PresentModeKHR presentMode : presentModes) {
			if (presentMode == vk::PresentModeKHR::eMailbox) {
				return presentMode;
			}
		}

		return vk::PresentModeKHR::eFifo;
	}

    vk::Extent2D ChooseSwapchainExtent(uint32_t width, uint32_t height, vk::SurfaceCapabilitiesKHR capabilities)
    {

		if (capabilities.currentExtent.width != UINT32_MAX) {
			return capabilities.currentExtent;
		}
		else {
			vk::Extent2D extent = { width, height };

			extent.width = std::min(
				capabilities.maxImageExtent.width, 
				std::max(capabilities.minImageExtent.width, extent.width)
			);

			extent.height = std::min(
				capabilities.maxImageExtent.height,
				std::max(capabilities.minImageExtent.height, extent.height)
			);

			return extent;
		}
	}

    SwapChainBundle MakeSwapchain(vk::Device logicalDevice, vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, int width, int height)
    {
        auto support = QuerySwapChainSupport(physicalDevice, surface);
        vk::SurfaceFormatKHR format = ChooseSwapchainSurfaceFormat(support.formats);
		vk::PresentModeKHR presentMode = ChooseSwapchainPresentMode(support.presentModes);
		vk::Extent2D extent = ChooseSwapchainExtent(width, height, support.capabilities);
		uint32_t imageCount = std::min(
			support.capabilities.maxImageCount,
			support.capabilities.minImageCount + 1
		);

		/*
        * VULKAN_HPP_CONSTEXPR SwapchainCreateInfoKHR(
            VULKAN_HPP_NAMESPACE::SwapchainCreateFlagsKHR flags_         = {},
            VULKAN_HPP_NAMESPACE::SurfaceKHR              surface_       = {},
            uint32_t                                      minImageCount_ = {},
            VULKAN_HPP_NAMESPACE::Format                  imageFormat_   = VULKAN_HPP_NAMESPACE::Format::eUndefined,
            VULKAN_HPP_NAMESPACE::ColorSpaceKHR   imageColorSpace_  = VULKAN_HPP_NAMESPACE::ColorSpaceKHR::eSrgbNonlinear,
            VULKAN_HPP_NAMESPACE::Extent2D        imageExtent_      = {},
            uint32_t                              imageArrayLayers_ = {},
            VULKAN_HPP_NAMESPACE::ImageUsageFlags imageUsage_       = {},
            VULKAN_HPP_NAMESPACE::SharingMode     imageSharingMode_ = VULKAN_HPP_NAMESPACE::SharingMode::eExclusive,
            uint32_t                              queueFamilyIndexCount_ = {},
            const uint32_t *                      pQueueFamilyIndices_   = {},
            VULKAN_HPP_NAMESPACE::SurfaceTransformFlagBitsKHR preTransform_ =
                VULKAN_HPP_NAMESPACE::SurfaceTransformFlagBitsKHR::eIdentity,
            VULKAN_HPP_NAMESPACE::CompositeAlphaFlagBitsKHR compositeAlpha_ =
                VULKAN_HPP_NAMESPACE::CompositeAlphaFlagBitsKHR::eOpaque,
            VULKAN_HPP_NAMESPACE::PresentModeKHR presentMode_  = VULKAN_HPP_NAMESPACE::PresentModeKHR::eImmediate,
            VULKAN_HPP_NAMESPACE::Bool32         clipped_      = {},
            VULKAN_HPP_NAMESPACE::SwapchainKHR   oldSwapchain_ = {} ) VULKAN_HPP_NOEXCEPT
		*/
        vk::SwapchainCreateInfoKHR createInfo = vk::SwapchainCreateInfoKHR(
			vk::SwapchainCreateFlagsKHR(), surface, imageCount, format.format, format.colorSpace,
			extent, 1, vk::ImageUsageFlagBits::eColorAttachment
		);

		VkUtil::QueueFamilyIndices indices = VkUtil::findQueueFamilies(physicalDevice, surface);
		uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

		if (indices.graphicsFamily != indices.presentFamily) {
			createInfo.imageSharingMode = vk::SharingMode::eConcurrent;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else {
			createInfo.imageSharingMode = vk::SharingMode::eExclusive;
		}

		createInfo.preTransform = support.capabilities.currentTransform;
		createInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;

		createInfo.oldSwapchain = vk::SwapchainKHR(nullptr);

        SwapChainBundle bundle{};
		try {
			bundle.swapchain = logicalDevice.createSwapchainKHR(createInfo);
		}
		catch (vk::SystemError err) {
			throw std::runtime_error("failed to create swap chain!");
		}

		std::vector<vk::Image> images = logicalDevice.getSwapchainImagesKHR(bundle.swapchain);
        bundle.frames.resize(images.size());

        for (size_t i = 0; i < images.size(); i++)
        {
            
            /**
             * ImageViewCreateInfo( VULKAN_HPP_NAMESPACE::ImageViewCreateFlags  flags_            = {},
                     VULKAN_HPP_NAMESPACE::Image                 image_            = {},
                    VULKAN_HPP_NAMESPACE::ImageViewType         viewType_         = VULKAN_HPP_NAMESPACE::ImageViewType::e1D,
                    VULKAN_HPP_NAMESPACE::Format                format_           = VULKAN_HPP_NAMESPACE::Format::eUndefined,
                    VULKAN_HPP_NAMESPACE::ComponentMapping      components_       = {},
                    VULKAN_HPP_NAMESPACE::ImageSubresourceRange subresourceRange_ = {},
                    const void *                                pNext_            = nullptr ) VULKAN_HPP_NOEXCEPT
                , flags( flags_ )
                , image( image_ )
                , viewType( viewType_ )
                , format( format_ )
                , components( components_ )
                , subresourceRange( subresourceRange_ )
            */
            vk::ImageViewCreateInfo createInfo = {};
            createInfo.image = images[i];
            createInfo.viewType = vk::ImageViewType::e2D;
            createInfo.format = format.format;
            createInfo.components.r = vk::ComponentSwizzle::eIdentity;
            createInfo.components.g = vk::ComponentSwizzle::eIdentity;
            createInfo.components.b = vk::ComponentSwizzle::eIdentity;
            createInfo.components.a = vk::ComponentSwizzle::eIdentity;
            createInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
            createInfo.subresourceRange.baseMipLevel = 0;
            createInfo.subresourceRange.levelCount = 1;
            createInfo.subresourceRange.baseArrayLayer = 0;
            createInfo.subresourceRange.layerCount = 1;
           
            bundle.frames[i].image = images[i];
            bundle.frames[i].imageView = logicalDevice.createImageView(createInfo);
        }

		bundle.format = format.format;
		bundle.extent = extent;

		return bundle;
    }
}