#include "Framebuffer.h"

namespace VkInit{

    void CreateFramebuffers(framebufferInput inputChunk, std::vector<VkUtil::SwapChainFrame>& frames)
    {
        for (int i = 0; i < frames.size(); ++i) {

            std::vector<vk::ImageView> attachments = {
                frames[i].imageView
            };

            vk::FramebufferCreateInfo framebufferInfo;
            framebufferInfo.flags = vk::FramebufferCreateFlags();
            framebufferInfo.renderPass = inputChunk.renderpass;
            framebufferInfo.attachmentCount = attachments.size();
            framebufferInfo.pAttachments = attachments.data();
            framebufferInfo.width = inputChunk.swapchainExtent.width;
            framebufferInfo.height = inputChunk.swapchainExtent.height;
            framebufferInfo.layers = 1;

            try {
                frames[i].frameBuffer = inputChunk.device.createFramebuffer(framebufferInfo);

                #ifdef ENABLE_VALIDATION_LAYER
                    std::cout << "Created framebuffer for frame " << i << std::endl;
                #endif
            }
            catch (vk::SystemError err) {
                #ifdef ENABLE_VALIDATION_LAYER
                    std::cout << "Failed to create framebuffer for frame " << i << std::endl;
                #endif
            }
        }
    }
}