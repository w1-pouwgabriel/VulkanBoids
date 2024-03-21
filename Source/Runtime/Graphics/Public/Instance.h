#pragma once
#include "Utils.h"

namespace VkInit 
{
    /**
        Check if extensions and layers are supported

		\param extensions a list of extension names being requested.
		\param layers a list of layer names being requested.
		\param debug whether to log error messages.
		\returns whether all of the extensions and layers are supported.
    */
	bool supported(std::vector<const char*>& extensions, std::vector<const char*>& layers);

	/**
		Create a Vulkan instance.

		\param applicationName the name of the application.
		\returns the instance created.
	*/
	vk::Instance MakeInstance(const char* applicationName);
}