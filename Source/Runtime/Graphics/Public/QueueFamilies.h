#pragma once

#include "Utils.h"

namespace VkUtil{

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	/**
		Check whether the given physical device has de needed families

		\param device the physical device to check.
		\returns a struct of QueueFamilyIndices
	*/
	QueueFamilyIndices findQueueFamilies(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface);
}