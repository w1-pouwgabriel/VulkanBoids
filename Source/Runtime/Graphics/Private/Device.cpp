#include "Device.h"

#include <set>

namespace VkInit
{
	void PrintDeviceOptions(const vk::PhysicalDevice& device) {

		/*	PhysicalDeviceProperties
		* 
			uint32_t                            apiVersion;
			uint32_t                            driverVersion;
			uint32_t                            vendorID;
			uint32_t                            deviceID;
			VkPhysicalDeviceType                deviceType;
			char                                deviceName[VK_MAX_PHYSICAL_DEVICE_NAME_SIZE];
			uint8_t                             pipelineCacheUUID[VK_UUID_SIZE];
			VkPhysicalDeviceLimits              limits;
			VkPhysicalDeviceSparseProperties    sparseProperties;
		*/
		
		vk::PhysicalDeviceProperties properties = device.getProperties();

		std::cout << "Device name: " << properties.deviceName << '\n';

		std::cout << "Device type: ";

		switch (properties.deviceType) {

		case (vk::PhysicalDeviceType::eCpu):
			std::cout << "CPU\n";
			break;

		case (vk::PhysicalDeviceType::eDiscreteGpu):
			std::cout << "Discrete GPU\n";
			break;

		case (vk::PhysicalDeviceType::eIntegratedGpu):
			std::cout << "Integrated GPU\n";
			break;

		case (vk::PhysicalDeviceType::eVirtualGpu):
			std::cout << "Virtual GPU\n";
			break;

		default:
			std::cout << "Other\n";
		}

	}

	bool checkDeviceExtensionSupport(const vk::PhysicalDevice& device, const std::vector<const char*>& requestedExtensions, const bool& debug)
	{
		/*
		* Check if a given physical device can satisfy a list of requested device
		* extensions.
		*/

		std::set<std::string> requiredExtensions(requestedExtensions.begin(), requestedExtensions.end());

		if (debug) {
			std::cout << "Device can support extensions:\n";
		}

		for (vk::ExtensionProperties& extension : device.enumerateDeviceExtensionProperties()) {

			if (debug) {
				std::cout << "\t\"" << extension.extensionName << "\"\n";
			}

			//remove this from the list of required extensions (set checks for equality automatically)
			requiredExtensions.erase(extension.extensionName);
		}

		//if the set is empty then all requirements have been satisfied
		return requiredExtensions.empty();
	}

	bool isSuitable(const vk::PhysicalDevice& device, const bool debug)
	{
		/*
		* A device is suitable if it can present to the screen, ie support
		* the swapchain extension
		*/
		std::vector<const char*> requestedExtensions{ 
			VK_KHR_SWAPCHAIN_EXTENSION_NAME 
		};

		if (debug) {
			std::cout << "We are requesting device extensions:\n";

			for (const char* extension : requestedExtensions) {
				std::cout << "\t\"" << extension << "\"\n";
			}

		}

		if (bool extensionsSupported = checkDeviceExtensionSupport(device, requestedExtensions, debug)) {

			if (debug) {
				std::cout << "Device can support the requested extensions!\n";
			}
		}
		else {

			if (debug) {
				std::cout << "Device can't support the requested extensions!\n";
			}

			return false;
		}
		return true;
	}

	QueueFamilyIndices findQueueFamilies(const vk::PhysicalDevice& device, const vk::SurfaceKHR& surface, const bool debug)
	{
		QueueFamilyIndices indices;

		std::vector<vk::QueueFamilyProperties> queueFamilyProperties = device.getQueueFamilyProperties();

		if (debug) {
			std::cout << "Supports " << queueFamilyProperties.size() << " different queue families\n";
		}

		int i = 0;
		for (vk::QueueFamilyProperties queueFam : queueFamilyProperties)
		{
			/*
			// Provided by VK_VERSION_1_0
			typedef enum VkQueueFlagBits {
				VK_QUEUE_GRAPHICS_BIT = 0x00000001,
				VK_QUEUE_COMPUTE_BIT = 0x00000002,
				VK_QUEUE_TRANSFER_BIT = 0x00000004,
				VK_QUEUE_SPARSE_BINDING_BIT = 0x00000008,
				VK_QUEUE_PROTECTED_BIT = 0x00000010,
				VK_QUEUE_VIDEO_DECODE_BIT_KHR = 0x00000020,
				VK_QUEUE_VIDEO_ENCODE_BIT_KHR = 0x00000040,
				VK_QUEUE_OPTICAL_FLOW_BIT_NV = 0x00000100,
			} VkQueueFlagBits;
			*/

			if (queueFam.queueFlags & vk::QueueFlagBits::eGraphics) {
				indices.graphicsFamily = i;

				if (debug) {
					std::cout << "Queue family " << i << " is chosen for graphics\n";
					std::cout << "This family supports " << queueFam.queueCount << " queues\n";
				}
			}
			if (device.getSurfaceSupportKHR(i, surface)) {
				indices.presentFamily = i;

				if (debug) {
					std::cout << "Queue family " << i << " is chosen for presenting\n";
				}
			}

			//If we were able to find all the queues that we need, break
			if (indices.isComplete()) {
				break;
			}

			i++;
		}

		return indices;
	}

	vk::PhysicalDevice MakePhysicalDevice(const vk::Instance& instance, const bool debug)
	{
		std::vector<vk::PhysicalDevice> devices = instance.enumeratePhysicalDevices();

		for (vk::PhysicalDevice device : devices) 
		{
			if (debug) {
				PrintDeviceOptions(device);
			}
			if (isSuitable(device, debug)) {
				return device;
			}
		}

		return vk::PhysicalDevice();
	}

	vk::Device MakeLogicalDevice(const vk::PhysicalDevice& physicalDevice, const vk::SurfaceKHR& surface, const bool debug)
	{
		QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface, debug);

		std::vector<uint32_t> uniqueFamIndices;
		uniqueFamIndices.push_back(indices.graphicsFamily.value());
		if (indices.graphicsFamily.value() != indices.presentFamily.value()) {
			uniqueFamIndices.push_back(indices.graphicsFamily.value());
		}

		/*
		DeviceQueueCreateInfo(VULKAN_HPP_NAMESPACE::DeviceQueueCreateFlags flags_            = {},
							  uint32_t                                     queueFamilyIndex_ = {},
							  uint32_t                                     queueCount_       = {},
							  const float *                                pQueuePriorities_ = {},
							  const void *                                 pNext_            = nullptr ) VULKAN_HPP_NOEXCEPT
		*/

		std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
		float queuePriority = 1.0f;
		for (uint32_t queueFamilyIndex : uniqueFamIndices) {
			queueCreateInfos.push_back(
				vk::DeviceQueueCreateInfo(
					vk::DeviceQueueCreateFlags(), queueFamilyIndex, 1, &queuePriority
				)
			);
		}

		vk::PhysicalDeviceFeatures deviceFeatures;
		//deviceFeatures.samplerAnisotropy = true;


		/*
		DeviceCreateInfo( VULKAN_HPP_NAMESPACE::DeviceCreateFlags              flags_                   = {},
		                  uint32_t                                             queueCreateInfoCount_    = {},
		                  const VULKAN_HPP_NAMESPACE::DeviceQueueCreateInfo *  pQueueCreateInfos_       = {},
		                  uint32_t                                             enabledLayerCount_       = {},
		                  const char * const *                                 ppEnabledLayerNames_     = {},
		                  uint32_t                                             enabledExtensionCount_   = {},
		                  const char * const *                                 ppEnabledExtensionNames_ = {},
		                  const VULKAN_HPP_NAMESPACE::PhysicalDeviceFeatures * pEnabledFeatures_        = {},
		                  const void *                                         pNext_                   = nullptr )
		*/

		std::vector<const char*> validationLayers;
		if (debug) {
			validationLayers.push_back("VK_LAYER_KHRONOS_validation");
		}

		vk::DeviceCreateInfo createInfo = vk::DeviceCreateInfo(
			vk::DeviceCreateFlags(),
			static_cast<uint32_t>(queueCreateInfos.size()), queueCreateInfos.data(),
			static_cast<uint32_t>(validationLayers.size()), validationLayers.data(),
			0, nullptr,
			&deviceFeatures
		);

		try {
			vk::Device device = physicalDevice.createDevice(createInfo);
			if (debug) {
				std::cout << "Logical device has correctly been created\n";
			}
			return device;
		}
		catch (vk::SystemError err) {
			std::cout << err.what() << std::endl;
		}

		return vk::Device();
	}

	std::array<vk::Queue, 2> GetQueues(const vk::PhysicalDevice& physicalDevice, const vk::Device& logicalDevice, const vk::SurfaceKHR& surface, const bool debug)
	{
		QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface, false);

		return { {
			logicalDevice.getQueue(indices.graphicsFamily.value(), 0),
			logicalDevice.getQueue(indices.presentFamily.value(), 0)
		} };
	}
}