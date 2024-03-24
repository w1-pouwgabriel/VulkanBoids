#pragma once

#include "Utils.h"

namespace VkInit 
{
    /**
    * Defualt Vulkan debugCallback
    */
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData) {

        std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

        return VK_FALSE;
    }

    /**
        Make a debug messenger

        \param instance The Vulkan instance which will be debugged.
        \param dispatchLoader dynamically loads instance based dispatch functions
        \returns the created messenger
    */
    vk::DebugUtilsMessengerEXT MakeDebugMessenger(vk::Instance& instance, vk::DispatchLoaderDynamic& dispatchLoader);

	/**
		Extract the transforms from the given bitmask.

		\param bits a bitmask describing various transforms
		\returns a vector of strings describing the transforms
	*/
	std::vector<std::string> LogTransformBits(vk::SurfaceTransformFlagsKHR bits);

	/**
		Extract the alpha composite blend modes from the given bitmask.

		\param bits a bitmask describing a combination of alpha composite options.
		\returns a vector of strings describing the options.
	*/
	std::vector<std::string> LogAlphaCompositeBits(vk::CompositeAlphaFlagsKHR bits);

	/**
		Extract image usage options.

		\param bits a bitmask describing various image usages
		\returns a vector of strings describing the image usages
	*/
	std::vector<std::string> LogImageUsageBits(vk::ImageUsageFlags bits);

	/**
		\returns a string description of the given present mode.
	*/
	std::string LogPresentMode(vk::PresentModeKHR presentMode);

	/**
		Print out the properties of the given physical device.

		\param device the physical device to investigate
	*/
	void PrintDeviceOptions(const vk::PhysicalDevice& device);

};

