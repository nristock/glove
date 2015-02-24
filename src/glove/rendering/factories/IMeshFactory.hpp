#pragma once

#include "glove/GloveApi.hpp"
#include "glove/rendering/Rendering.hpp"
#include "glove/services/Services.hpp"

namespace glove {

/// @ingroup RenderServices
class GLOVE_API_EXPORT IMeshFactory : public BasicService {
  public:
    static ServiceType serviceType;

    IMeshFactory() : BasicService(serviceType) {}
    virtual ~IMeshFactory(){};

    virtual IMeshPtr CreatedIndexedMesh(const IMaterialPtr& material, const IVertexDataPtr& vertexData,
                                        const IIndexDataPtr& indexData) = 0;
    virtual IMeshPtr CreateMesh(const IMaterialPtr& material, const IVertexDataPtr& vertexData) = 0;
    virtual IMeshPtr CreateEmptyMesh(const IMaterialPtr& material) const = 0;
};
}