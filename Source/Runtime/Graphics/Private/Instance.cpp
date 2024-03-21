#include "Instance.h"

namespace VkInit
{
	bool supported(std::vector<const char*>& extensions, std::vector<const char*>& layers)
	{
		//check extension support
		std::vector<vk::ExtensionProperties> supportedExtensions = vk::enumerateInstanceExtensionProperties();

		#if ENABLE_VALIDATION_LAYER
			std::cout << "Device can support the following extensions:\n";
			for (vk::ExtensionProperties supportedExtension : supportedExtensions) {
				std::cout << '\t' << supportedExtension.extensionName << '\n';
			}
		#endif

		bool found = false;
		for (const char* extension : extensions) {
			for (vk::ExtensionProperties supportedExtension : supportedExtensions) {
				if (strcmp(extension, supportedExtension.extensionName) == 0) {
					found = true;
					#if ENABLE_VALIDATION_LAYER
						std::cout << "Extension \"" << extension << "\" is supported!\n";
					#endif
				}
			}
			if (!found) {
				#if ENABLE_VALIDATION_LAYER
					std::cout << "Extension \"" << extension << "\" is not supported!\n";
				#endif
				return false;
			}
		}

		//check extension support
		std::vector<vk::LayerProperties> supportedLayers = vk::enumerateInstanceLayerProperties();

		#if ENABLE_VALIDATION_LAYER
			std::cout << "Device can support the following extensions:\n";
			for (vk::LayerProperties supportedLayer : supportedLayers) {
				std::cout << '\t' << supportedLayer.layerName << '\n';
			}
		#endif

		for (const char* layer : layers) {
			found = false;
			for (vk::LayerProperties supportedExtension : supportedLayers) {
				if (strcmp(layer, supportedExtension.layerName) == 0) {
					found = true;
					#if ENABLE_VALIDATION_LAYER
						std::cout << "Layer \"" << layer << "\" is supported!\n";
					#endif
				}
			}
			if (!found) {
				#if ENABLE_VALIDATION_LAYER
					std::cout << "Layer \"" << layer << "\" is not supported!\n";
				#endif
				return false;
			}
		}

		return true;
	}

	vk::Instance MakeInstance(const char* applicationName)
	{
		uint32_t version{ 0 };
		vkEnumerateInstanceVersion(&version);

		#if ENABLE_VALIDATION_LAYER
			std::cout << "System can support vulkan Variant: " << VK_API_VERSION_VARIANT(version)
				<< ", Major: " << VK_API_VERSION_MAJOR(version)
				<< ", Minor: " << VK_API_VERSION_MINOR(version)
				<< ", Patch: " << VK_API_VERSION_PATCH(version) << '\n';
		#endif

		//Use the lastest version
		// remove the last 8 bits
		version &= ~(0xFFFU);

		version = VK_MAKE_API_VERSION(0, 1, 0, 0);

		vk::ApplicationInfo appInfo = vk::ApplicationInfo(
			applicationName,
			version,
			"Why not",
			version,
			version
		);

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
		#if ENABLE_VALIDATION_LAYER
			extensions.push_back("VK_EXT_debug_utils");
		
			std::cout << "extensions to be requested:\n";

			for (const char* var : extensions)
			{
				std::cout << "\t\"" << var << "\"\n";
			}
		#endif

		std::vector<const char*> validationLayers;
		#if ENABLE_VALIDATION_LAYER
			validationLayers.push_back("VK_LAYER_KHRONOS_validation");
		#endif

		if (!supported(extensions, validationLayers)) {
			return nullptr;
		}

		vk::InstanceCreateInfo createInfo = vk::InstanceCreateInfo(
			vk::InstanceCreateFlags(),
			&appInfo,
			static_cast<uint32_t>(validationLayers.size()),
			validationLayers.data(),
			static_cast<uint32_t>(extensions.size()),
			extensions.data()
		);

		try
		{
			return vk::createInstance(createInfo, nullptr);
		}
		catch (const vk::SystemError err)
		{
			#if ENABLE_VALIDATION_LAYER
				std::cout << "Failed to create instance: " << err.what() << "\n";
			#endif
		}

		return nullptr;
	}
}