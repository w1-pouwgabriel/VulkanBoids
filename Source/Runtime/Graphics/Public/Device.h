#pragma once
#include "Utils.h"

namespace VkInit 
{
	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	/**
		Print out the properties of the given physical device.

		\param device the physical device to investigate
	*/
	void PrintDeviceOptions(const vk::PhysicalDevice& device);

	/**
		Check whether the physical device can support the given extensions.

		\param device the physical device to check
		\param requestedExtensions a list of extension names to check against
		\returns whether all of the extensions are requested
	*/
	bool checkDeviceExtensionSupport(
		const vk::PhysicalDevice& device,
		const std::vector<const char*>& requestedExtensions
	);

	/**
		Check whether the given physical device is suitable for the system.

		\param device the physical device to check.
		\returns whether the device is suitable.
	*/
	bool isSuitable(const vk::PhysicalDevice& device);

	/**
		Check whether the given physical device has de needed families

		\param device the physical device to check.
		\returns a struct of QueueFamilyIndices
	*/
	QueueFamilyIndices findQueueFamilies(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface);
	
	/**
		Choose a physical device based on the best hardware

		\param instance the vulkan instance to use
		\returns the chosen physical device
	*/
	vk::PhysicalDevice MakePhysicalDevice(const vk::Instance& instance);

	/**
		Create a logical device based on the physical device

		\param physicalDevice the physical device that we are using
		\param surface the surface is needed to check for queue families
		\returns the logical device
	*/
	vk::Device MakeLogicalDevice(const vk::PhysicalDevice& physicalDevice, const vk::SurfaceKHR& surface);

	/**
		Get the queues

		\param physicalDevice the physical device that we are using
		\param logicalDevice the logical device
		\param surface the surface is needed to check for queue families
		\returns the queues
	*/
	std::array<vk::Queue, 2> GetQueues(const vk::PhysicalDevice& physicalDevice, const vk::Device& logicalDevice, const vk::SurfaceKHR& surface);
}