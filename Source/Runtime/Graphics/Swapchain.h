#pragma once
#include "Utils.h"

namespace VkInit
{
	/**
		capabilities: no. of images and supported sizes
		formats: eg. supported pixel formats
		present modes: available presentation modes (eg. double buffer, fifo, mailbox)
	*/
	struct SwapChainSupportDetails {
		vk::SurfaceCapabilitiesKHR capabilities;
		std::vector<vk::SurfaceFormatKHR> formats;
		std::vector<vk::PresentModeKHR> presentModes;
	};

	/**
		Go through all the swapchain options and see which ones are available to us.

		\param device
		\param surface
		\returns struct with all the data that we need for the creation process
	*/
	SwapChainSupportDetails QuerySwapChainSupport(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface);

	/*
	* https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Image_views
	* VkImage == vk::Image
		To use any VkImage, including those in the swap chain,
		in the render pipeline we have to create a VkImageView object.
		An image view is quite literally a view into an image.
		It describes how to access the image and which part of the image to access,
		for example if it should be treated as a 2D texture depth texture without any mipmapping levels.
	*/
}