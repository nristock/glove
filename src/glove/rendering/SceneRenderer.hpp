#pragma once

#include <memory>
#include "glove/GloveApi.hpp"

namespace glove {
class RenderHardwareInterface;
using RenderHardwareInterfaceHandle = std::shared_ptr<RenderHardwareInterface>;

class Scene;
using SceneHandle = std::shared_ptr<Scene>;

struct SceneView;
class SceneViewComposition;

class RenderCommandList;

class RenderTarget;

class GLOVE_API_EXPORT SceneRenderer {
  public:
    SceneRenderer(SceneHandle scene, RenderHardwareInterfaceHandle renderer) : scene(scene), renderer(renderer) {}
    virtual ~SceneRenderer() = default;

    virtual void CreateResources() = 0;

    /// Returns the final color target which can be used for post-processing effects
    virtual void RenderComposition(SceneViewComposition& composition, RenderCommandList& renderCommandList, RenderTarget& renderTarget) = 0;

  protected:
    SceneHandle scene;
    RenderHardwareInterfaceHandle renderer;
};

} /* namespace glove */