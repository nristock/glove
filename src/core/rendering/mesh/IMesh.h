#pragma once

#include "../Rendering.h"

namespace glove {

/// @ingroup RenderSubsystemInterface
class IMesh {
  public:
    virtual ~IMesh() = default;

    /// @brief Changes the mesh's material and does everything required to update buffer data/vertex layout bindings.
    virtual void BindMaterial(const IMaterialPtr& material) = 0;

    virtual const IMaterialPtr& GetMaterial() const = 0;
    virtual const IVertexDataPtr& GetVertexData() const = 0;
    virtual const IIndexDataPtr& GetIndexData() const = 0;
};

} // namespace glove