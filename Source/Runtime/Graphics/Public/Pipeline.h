#pragma once

#include "Utils.h"
#include "Shaders.h"

namespace vkInit {
    /**
		holds the data structures used to create a pipeline
	*/
	struct GraphicsPipelineInBundle {
		vk::Device device;
		std::string vertexFilepath;
		std::string fragmentFilepath;
		vk::Extent2D swapchainExtent;
		vk::Format swapchainImageFormat;
	};

	/**
		Used for returning the pipeline, along with associated data structures,
		after creation.
	*/
	struct GraphicsPipelineOutBundle {
		vk::PipelineLayout layout;
		vk::RenderPass renderpass;
		vk::Pipeline pipeline;
	};

	/**
		Make a pipeline layout, this consists mostly of describing the
		push constants and descriptor set layouts which will be used.

		\param device the logical device
		\returns the created pipeline layout
	*/
	vk::PipelineLayout MakePipelineLayout(vk::Device device);

	/**
		Make a renderpass, a renderpass describes the subpasses involved
		as well as the attachments which will be used.

		\param device the logical device
		\param swapchainImageFormat the image format chosen for the swapchain images
		\returns the created renderpass
	*/
	vk::RenderPass MakeRenderpass(vk::Device device, vk::Format swapchainImageFormat);

	/**
		Make a graphics pipeline, along with renderpass and pipeline layout

		\param specification the struct holding input data, as specified at the top of the file.
		\returns the bundle of data structures created
	*/
	GraphicsPipelineOutBundle CreateGraphicsPipeline(GraphicsPipelineInBundle& specification);
}