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

	std::vector<std::string> LogTransformBits(vk::SurfaceTransformFlagsKHR bits) {
		std::vector<std::string> result;

		/*
			* typedef enum VkSurfaceTransformFlagBitsKHR {
				VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR = 0x00000001,
				VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR = 0x00000002,
				VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR = 0x00000004,
				VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR = 0x00000008,
				VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR = 0x00000010,
				VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR = 0x00000020,
				VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR = 0x00000040,
				VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR = 0x00000080,
				VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR = 0x00000100,
			} VkSurfaceTransformFlagBitsKHR;
		*/
		if (bits & vk::SurfaceTransformFlagBitsKHR::eIdentity) {
			result.push_back("identity");
		}
		if (bits & vk::SurfaceTransformFlagBitsKHR::eRotate90) {
			result.push_back("90 degree rotation");
		}
		if (bits & vk::SurfaceTransformFlagBitsKHR::eRotate180) {
			result.push_back("180 degree rotation");
		}
		if (bits & vk::SurfaceTransformFlagBitsKHR::eRotate270) {
			result.push_back("270 degree rotation");
		}
		if (bits & vk::SurfaceTransformFlagBitsKHR::eHorizontalMirror) {
			result.push_back("horizontal mirror");
		}
		if (bits & vk::SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate90) {
			result.push_back("horizontal mirror, then 90 degree rotation");
		}
		if (bits & vk::SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate180) {
			result.push_back("horizontal mirror, then 180 degree rotation");
		}
		if (bits & vk::SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate270) {
			result.push_back("horizontal mirror, then 270 degree rotation");
		}
		if (bits & vk::SurfaceTransformFlagBitsKHR::eInherit) {
			result.push_back("inherited");
		}

		return result;
	}

	std::vector<std::string> LogAlphaCompositeBits(vk::CompositeAlphaFlagsKHR bits) {
		std::vector<std::string> result;

		/*
			typedef enum VkCompositeAlphaFlagBitsKHR {
				VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR = 0x00000001,
				VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR = 0x00000002,
				VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR = 0x00000004,
				VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR = 0x00000008,
			} VkCompositeAlphaFlagBitsKHR;
		*/
		if (bits & vk::CompositeAlphaFlagBitsKHR::eOpaque) {
			result.push_back("opaque (alpha ignored)");
		}
		if (bits & vk::CompositeAlphaFlagBitsKHR::ePreMultiplied) {
			result.push_back("pre multiplied (alpha expected to already be multiplied in image)");
		}
		if (bits & vk::CompositeAlphaFlagBitsKHR::ePostMultiplied) {
			result.push_back("post multiplied (alpha will be applied during composition)");
		}
		if (bits & vk::CompositeAlphaFlagBitsKHR::eInherit) {
			result.push_back("inherited");
		}

		return result;
	}

	std::vector<std::string> LogImageUsageBits(vk::ImageUsageFlags bits) {
		std::vector<std::string> result;

		/*
		* Alot of these options wont be available to us becuase they are meant for mobile or other
		* 
		  enum class ImageUsageFlagBits : VkImageUsageFlags {
			eTransferSrc                      = VK_IMAGE_USAGE_TRANSFER_SRC_BIT,
			eTransferDst                      = VK_IMAGE_USAGE_TRANSFER_DST_BIT,
			eSampled                          = VK_IMAGE_USAGE_SAMPLED_BIT,
			eStorage                          = VK_IMAGE_USAGE_STORAGE_BIT,
			eColorAttachment                  = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
			eDepthStencilAttachment           = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
			eTransientAttachment              = VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT,
			eInputAttachment                  = VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT,
			eVideoDecodeDstKHR                = VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR,
			eVideoDecodeSrcKHR                = VK_IMAGE_USAGE_VIDEO_DECODE_SRC_BIT_KHR,
			eVideoDecodeDpbKHR                = VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR,
			eShadingRateImageNV               = VK_IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV,
			eFragmentDensityMapEXT            = VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT,
			eFragmentShadingRateAttachmentKHR = VK_IMAGE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR,
			eHostTransferEXT                  = VK_IMAGE_USAGE_HOST_TRANSFER_BIT_EXT,
			eVideoEncodeDstKHR                = VK_IMAGE_USAGE_VIDEO_ENCODE_DST_BIT_KHR,
			eVideoEncodeSrcKHR                = VK_IMAGE_USAGE_VIDEO_ENCODE_SRC_BIT_KHR,
			eVideoEncodeDpbKHR                = VK_IMAGE_USAGE_VIDEO_ENCODE_DPB_BIT_KHR,
			eAttachmentFeedbackLoopEXT        = VK_IMAGE_USAGE_ATTACHMENT_FEEDBACK_LOOP_BIT_EXT,
			eInvocationMaskHUAWEI             = VK_IMAGE_USAGE_INVOCATION_MASK_BIT_HUAWEI,
			eSampleWeightQCOM                 = VK_IMAGE_USAGE_SAMPLE_WEIGHT_BIT_QCOM,
			eSampleBlockMatchQCOM             = VK_IMAGE_USAGE_SAMPLE_BLOCK_MATCH_BIT_QCOM
			};
		*/

		if (bits & vk::ImageUsageFlagBits::eTransferSrc) {
			result.push_back("transfer src: image can be used as the source of a transfer command.");
		}
		if (bits & vk::ImageUsageFlagBits::eTransferDst) {
			result.push_back("transfer dst: image can be used as the destination of a transfer command.");
		}
		if (bits & vk::ImageUsageFlagBits::eSampled) {
			result.push_back("sampled: image can be used to create a VkImageView suitable for occupying a VkDescriptorSet slot either of type VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE or VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, and be sampled by a shader.");
		}
		if (bits & vk::ImageUsageFlagBits::eStorage) {
			result.push_back("storage: image can be used to create a VkImageView suitable for occupying a VkDescriptorSet slot of type VK_DESCRIPTOR_TYPE_STORAGE_IMAGE.");
		}
		if (bits & vk::ImageUsageFlagBits::eColorAttachment) {
			result.push_back("color attachment: image can be used to create a VkImageView suitable for use as a color or resolve attachment in a VkFramebuffer.");
		}
		if (bits & vk::ImageUsageFlagBits::eDepthStencilAttachment) {
			result.push_back("depth/stencil attachment: image can be used to create a VkImageView suitable for use as a depth/stencil or depth/stencil resolve attachment in a VkFramebuffer.");
		}
		if (bits & vk::ImageUsageFlagBits::eTransientAttachment) {
			result.push_back("transient attachment: implementations may support using memory allocations with the VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT to back an image with this usage. \
This bit can be set for any image that can be used to create a VkImageView suitable for use as a color, resolve, depth/stencil, or input attachment.");
		}
		if (bits & vk::ImageUsageFlagBits::eInputAttachment) {
			result.push_back("input attachment: image can be used to create a VkImageView suitable for occupying VkDescriptorSet slot of type VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT; be read from \
a shader as an input attachment; and be used as an input attachment in a framebuffer.");
		}
		if (bits & vk::ImageUsageFlagBits::eFragmentDensityMapEXT) {
			result.push_back("fragment density map: image can be used to create a VkImageView suitable \
for use as a fragment density map image.");
		}
		if (bits & vk::ImageUsageFlagBits::eFragmentShadingRateAttachmentKHR) {
			result.push_back("fragment shading rate attachment: image can be used to create a VkImageView \
suitable for use as a fragment shading rate attachment or shading rate image");
		}
		return result;
	}

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
}
