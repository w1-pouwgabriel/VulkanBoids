#include "Pipeline.h"

namespace vkInit {

    vk::PipelineLayout MakePipelineLayout(vk::Device device) 
    {
		vk::PipelineLayoutCreateInfo layoutInfo;
		layoutInfo.flags = vk::PipelineLayoutCreateFlags();
		layoutInfo.setLayoutCount = 0;
		layoutInfo.pushConstantRangeCount = 0;
		try {
			return device.createPipelineLayout(layoutInfo);
		}
		catch (vk::SystemError err) {
			#if ENABLE_VALIDATION_LAYER
				std::cout << "Failed to create pipeline layout!" << std::endl;
			#endif
		}
		return vk::PipelineLayout{}; // return emtpy
	}

    GraphicsPipelineOutBundle CreateGraphicsPipeline(GraphicsPipelineInBundle &specification)
    {
		GraphicsPipelineOutBundle output{};

        return output;
    }
}
