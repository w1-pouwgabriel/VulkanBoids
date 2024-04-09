#include "Shaders.h"

namespace vkUtil {

    std::vector<char> readFile(std::string filename, bool debug) 
	{
		std::ifstream file(filename, std::ios::ate | std::ios::binary);

		if (debug && !file.is_open()) {
			std::cout << "Failed to load \"" << filename << "\"" << std::endl;
		}

		size_t filesize{ static_cast<size_t>(file.tellg()) };

		std::vector<char> buffer(filesize);
		file.seekg(0);
		file.read(buffer.data(), filesize);

		file.close();
		return buffer;
	}
    
	vk::ShaderModule CreateModule(std::string filename, vk::Device device) 
	{
		std::vector<char> sourceCode = readFile(filename);
		vk::ShaderModuleCreateInfo moduleInfo = {};
		moduleInfo.flags = vk::ShaderModuleCreateFlags();
		moduleInfo.codeSize = sourceCode.size();
		moduleInfo.pCode = reinterpret_cast<const uint32_t*>(sourceCode.data());

		try {
			return device.createShaderModule(moduleInfo);
		}
		catch (vk::SystemError err) {
			#if ENABLE_VALIDATION_LAYER
				std::cout << "Failed to create shader module for \"" << filename << "\"" << std::endl;
			#endif
		}
		return vk::ShaderModule{};
	}

}
