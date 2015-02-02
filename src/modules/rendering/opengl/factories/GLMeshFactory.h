#pragma once

#include <glove/rendering/factories/IMeshFactory.h>

namespace glove {
namespace gl {

/// @ingroup Factories
class GLMeshFactory : public IMeshFactory {
  public:
    virtual IMeshPtr CreatedIndexedMesh(const IMaterialPtr& material, const IVertexDataPtr& vertexData,
                                        const IIndexDataPtr& indexData);
    virtual IMeshPtr CreateMesh(const IMaterialPtr& material, const IVertexDataPtr& vertexData);
    virtual IMeshPtr CreateEmptyMesh(const IMaterialPtr& material) const;
};
}
}