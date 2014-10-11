#pragma once

#include "core/GloveFwd.h"
#include "rendering/FrameData.h"

namespace glove {

class IRenderer {
public:
    virtual void Init() = 0;
    virtual void Exit() = 0;

    virtual GloveWindowPtr CreateWindow(int windowWidth, int windowHeight) = 0;

    virtual void ClearBuffers() = 0;
    virtual void RenderScene(ScenegraphPointer scenegraph, FrameData& frameData) = 0;
    virtual void SwapBuffers() = 0;

    virtual GloveWindowPtr GetActiveWindow() const = 0;
    virtual void SetActiveWindow(unsigned short id) = 0;
    virtual size_t GetWindowCount() const = 0;

    virtual void CreateVertexAttributeMappings(IMesh* mesh) = 0;

    virtual void PollSystemEvents() = 0;
};

} /* namespace glove */