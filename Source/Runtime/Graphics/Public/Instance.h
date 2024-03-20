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
	bool supported(std::vector<const char*>& extensions, std::vector<const char*>& layers, bool debug);

	/**
		Create a Vulkan instance.

		\param debug whether the system is being run in debug mode.
		\param applicationName the name of the application.
		\returns the instance created.
	*/
	vk::Instance MakeInstance(bool debug, const char* applicationName);
}