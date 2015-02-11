#pragma once

#include "glove/GloveFwd.hpp"

#include "glove/rendering/Rendering.hpp"
#include "glove/rendering/FrameData.hpp"
#include "glove/rendering/mesh/IMesh.hpp"

namespace glove {

/// @brief Abstract mesh base class to be used by render system implementations.
/// @ingroup RenderSubsystemInterface
///
/// Note: Rendering *always* requires an IMaterial instance to be bound. Binding a material (which basically is a shader
/// program) and the corresponding IVertexAttributeMapping to the vertex data's VertexLayout is very implementation
/// specific. Thus, material binding has to be implemented by the render system implementation.
class Mesh : public IMesh {
  public:
    Mesh(const IVertexDataPtr& vertexData, const IIndexDataPtr& indexData);

    virtual const IMaterialPtr& GetMaterial() const;
    virtual const IVertexDataPtr& GetVertexData() const;
    virtual const IIndexDataPtr& GetIndexData() const;

  protected:
    IVertexDataPtr vertexData;
    IIndexDataPtr indexData;
    IMaterialPtr material;
};

} /* namespace glove */