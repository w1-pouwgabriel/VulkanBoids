#include "Logging.h"

namespace VkInit 
{

    vk::DebugUtilsMessengerEXT MakeDebugMessenger(vk::Instance& instance, vk::DispatchLoaderDynamic& dispatchLoader)
    {
        vk::DebugUtilsMessengerCreateInfoEXT createInfo = vk::DebugUtilsMessengerCreateInfoEXT(
            vk::DebugUtilsMessengerCreateFlagsEXT(),
            vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError,
            vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
            debugCallback,
            nullptr
        );
        
        return instance.createDebugUtilsMessengerEXT(createInfo, nullptr, dispatchLoader);
    }
}
