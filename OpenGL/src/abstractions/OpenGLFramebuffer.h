#pragma once

#include <cstdint> 

namespace Vipera {

	struct FramebufferSpecification
	{
		uint32_t Width, Height;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class OpenGLFramebuffer
	{
	public:
		OpenGLFramebuffer();
		virtual ~OpenGLFramebuffer();

		void SetNewParametrs(uint32_t width, uint32_t height);
			
		virtual uint32_t GetColorAttachmentTexID() const { return mColorTexID; }
		virtual const FramebufferSpecification& GetSpecification() const { return mSpecification; }

		void Bind();
		void Unbind();
	private:
		uint32_t mRendererID;
		uint32_t mColorTexID, mDepthTexID;
		FramebufferSpecification mSpecification;
	};
}