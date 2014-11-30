#pragma once

#include "Rendering.h"
#include "RenderOperation.h"

namespace glove {

/// @ingroup RenderSubsystemInterface
class IRenderable {
public:
	virtual ~IRenderable() {};

	/// @brief Invoked by the rendering system to set up the rendering operation.
	virtual void SetupRender(RenderOperation& renderOp, const FrameData& frameData) = 0;
	/// @brief Invoked by the rendering system just after the object has been rendered.
	virtual void PostRender(RenderOperation& renderOp, const FrameData& frameData) = 0;
};

} /* namespace glove */