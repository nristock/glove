#pragma once

#include <unordered_set>

#include "glove/rendering/IRenderer.h"

namespace glove {

/// @ingroup RenderSubsystemInterface
class RendererBase : public IRenderer, public std::enable_shared_from_this<RendererBase> {
public:
    virtual ~RendererBase() = default;

    virtual void MapCameraToTarget(const CameraBaseHandle& camera, const RenderTargetHandle& renderTarget);
    virtual void RenderScene(const ScenegraphHandle& scenegraph, const RenderTargetHandle& renderTarget);

protected:
    typedef std::multimap<RenderTargetHandle, CameraBaseHandle> CameraTargetMapping;
    typedef std::pair<CameraTargetMapping::iterator, CameraTargetMapping::iterator> CameraTargetMappingRange;

    CameraTargetMapping cameraTargetMapping;

    virtual void RenderSceneToTarget(const ScenegraphHandle& scenegraph, const RenderTargetHandle& renderTarget, std::unordered_set<RenderTargetHandle>& renderedTargets);
};

} /* namespace glove */