#pragma once

#include "glove/rendering/Rendering.hpp"

namespace glove {

/// @ingroup RenderSubsystemInterface
class GLOVE_API_EXPORT IMesh {
  public:
    virtual ~IMesh() = default;

    /// @brief Changes the mesh's material and does everything required to update buffer data/vertex layout bindings.
    virtual void BindMaterial(const IMaterialPtr& material) = 0;

    virtual const IMaterialPtr& GetMaterial() const = 0;
    virtual const IVertexDataPtr& GetVertexData() const = 0;
    virtual const IIndexDataPtr& GetIndexData() const = 0;
};

} // namespace glove