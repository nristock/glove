#pragma once

#include "glove/GloveApi.hpp"
#include "glove/rendering/Rendering.hpp"

namespace glove {

/// @ingroup RenderSubsystemInterface
class GLOVE_API_EXPORT IMeshFactory {
  public:
    virtual ~IMeshFactory(){};

    virtual IMeshPtr CreatedIndexedMesh(const IMaterialPtr& material, const IVertexDataPtr& vertexData,
                                        const IIndexDataPtr& indexData) = 0;
    virtual IMeshPtr CreateMesh(const IMaterialPtr& material, const IVertexDataPtr& vertexData) = 0;
    virtual IMeshPtr CreateEmptyMesh(const IMaterialPtr& material) const = 0;
};
}