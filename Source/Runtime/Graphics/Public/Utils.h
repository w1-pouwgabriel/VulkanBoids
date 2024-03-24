#pragma once

#include <vulkan/vulkan.hpp>

/*
* including the prebuilt header from the lunarg sdk will load
* most functions, but not all.
*
* Functions can also be dynamically loaded, using the call
*
* PFN_vkVoidFunction vkGetInstanceProcAddr(
	VkInstance                                  instance,
	const char*                                 pName);

 or

 PFN_vkVoidFunction vkGetDeviceProcAddr(
	VkDevice                                    device,
	const char*                                 pName);

*/

#include <GLFW/glfw3.h>

#include <iostream>
#include <optional>
#include <vector>