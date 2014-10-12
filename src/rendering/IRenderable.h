#pragma once

namespace glove {

struct FrameData;
struct RenderOperation;

class IRenderable {
public:
	virtual ~IRenderable() {};

	/** Invoked by the rendering system to set up the rendering operation. */
	virtual void SetupRender(RenderOperation& renderOp, const FrameData& frameData) = 0;
	/** Invoked by the rendering system just after the object has been rendered. */
	virtual void PostRender(RenderOperation& renderOp, const FrameData& frameData) = 0;
};

} /* namespace glove */
