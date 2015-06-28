#pragma once

#include <list>

#include "glove/BlueDwarfApi.hpp"
#include "glove/rendering/MeshBatch.hpp"

namespace BlueDwarf {
class RenderCommandList;
struct SceneView;

class BD_API_EXPORT PrimitiveDrawInterface {
  public:
    virtual ~PrimitiveDrawInterface() = default;

    virtual void DrawMesh(const MeshBatch& meshBatch) = 0;
};

class BD_API_EXPORT BatchCollector : public PrimitiveDrawInterface {
  public:
    virtual void DrawMesh(const MeshBatch& meshBatch);

    void DrawBatches(RenderCommandList& cmdList, const SceneView& view);

  protected:
    void DrawBatch(const MeshBatch& batch, RenderCommandList& cmdList, const SceneView& view);

    std::list<MeshBatch> meshBatches;
};
}