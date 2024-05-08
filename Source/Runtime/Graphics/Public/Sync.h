#pragma once

#include "Utils.h"

namespace VkInit 
{
    /**
		Make a semaphore.

		\param device the logical device
		\param debug whether the system is running in debug mode
		\returns the created semaphore
	*/
	vk::Semaphore CreateSemaphore(vk::Device device);

	/**
		Make a fence.

		\param device the logical device
		\param debug whether the system is running in debug mode
		\returns the created fence
	*/
	vk::Fence CreateFence(vk::Device device);
}