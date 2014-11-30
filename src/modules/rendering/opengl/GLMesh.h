#pragma once

#include <core/rendering/mesh/Mesh.h>

#include "GLRenderer.h"
#include "GLBaseMesh.h"

namespace glove {
namespace gl {

/// @ingroup OpenGLRenderer
class GLMesh : public GLBaseMesh, public Mesh {
  public:
    GLMesh(const IMaterialPtr& material, const IVertexDataPtr& vertexData, const IIndexDataPtr& indexData);
    GLMesh(const GLMesh&) = delete;
    GLMesh& operator=(const GLMesh&) = delete;

    virtual void BindMaterial(const IMaterialPtr& material);

  protected:
    virtual void InitVertexAttributeObjectStateForContext(ContextId contextId);
    void SetupVertexAttribute(const IVertexAttributeMappingPtr& shaderProgramAttributeMapping,
                              VertexLayout& vertexLayout, const VertexAttribute& vertexAttribute);

  private:
    logging::GloveLogger logger;
};
}
} // namespace glove