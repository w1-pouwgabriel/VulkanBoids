#pragma once

#include "Utils.h"
#include "Frame.h"

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
		Various data structures associated with the swapchain.
	*/
	struct SwapChainBundle {
		vk::SwapchainKHR swapchain;
		std::vector<VkUtil::SwapChainFrame> frames;
		vk::Format format;
		vk::Extent2D extent;
	};

	/**
		Go through all the swapchain options and see which ones are available to us.

		\param device PhysicalDevice
		\param surface SurfaceKHR
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

	/**
		Choose a surface format for the swapchain

		\param formats a vector of surface formats supported by the device
		\returns the chosen format
	*/
	vk::SurfaceFormatKHR ChooseSwapchainSurfaceFormat(std::vector<vk::SurfaceFormatKHR> formats);

	/**
		Choose a present mode.

		\param presentModes a vector of present modes supported by the device
		\returns the chosen present mode
	*/
	vk::PresentModeKHR ChooseSwapchainPresentMode(std::vector<vk::PresentModeKHR> presentModes);

	/**
		Choose an extent for the swapchain.

		\param width the requested width
		\param height the requested height
		\param capabilities a struct describing the supported capabilities of the device
		\returns the chosen extent
	*/
	vk::Extent2D ChooseSwapchainExtent(uint32_t width, uint32_t height, vk::SurfaceCapabilitiesKHR capabilities);

	/**
		Create a swapchain

		\param logicalDevice the logical device
		\param physicalDevice the physical device
		\param surface the window surface to use the swapchain with
		\param width the requested width
		\param height the requested height
		\returns a struct holding the swapchain and other associated data structures
	*/
	SwapChainBundle CreateSwapchain(vk::Device logicalDevice, vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, int width, int height);
}