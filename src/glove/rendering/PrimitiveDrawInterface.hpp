#pragma once

#include <list>

#include "glove/GloveApi.hpp"
#include "glove/rendering/MeshBatch.hpp"

namespace glove {
class RenderCommandList;
struct SceneView;

class GLOVE_API_EXPORT PrimitiveDrawInterface {
  public:
    virtual ~PrimitiveDrawInterface() = default;

    virtual void DrawMesh(const MeshBatch& meshBatch) = 0;
};

class GLOVE_API_EXPORT BatchCollector : public PrimitiveDrawInterface {
  public:
    virtual void DrawMesh(const MeshBatch& meshBatch);

    void DrawBatches(RenderCommandList& cmdList, const SceneView& view);

  protected:
    void DrawBatch(const MeshBatch& batch, RenderCommandList& cmdList, const SceneView& view);

    std::list<MeshBatch> meshBatches;
};
}