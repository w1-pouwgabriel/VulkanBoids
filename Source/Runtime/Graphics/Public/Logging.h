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
};

