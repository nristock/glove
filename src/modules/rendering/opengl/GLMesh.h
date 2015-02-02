#pragma once

#include <map>
#include <GL/glew.h>

#include <glove/rendering/mesh/Mesh.h>
#include <glove/rendering/IRenderer.h>

#include "GLRenderer.h"

namespace glove {
namespace gl {

/// @ingroup OpenGLRenderer
class GLMesh : public Mesh {
  public:
    GLMesh(const IMaterialPtr& material, const IVertexDataPtr& vertexData, const IIndexDataPtr& indexData);
    GLMesh(const GLMesh&) = delete;
    GLMesh& operator=(const GLMesh&) = delete;

    virtual void BindMaterial(const IMaterialPtr& material);

  virtual ~GLMesh();

  const GLuint GetVertexArrayId(ContextId contextId);

  void EnsureVertexArrayObjectExistsForContext(ContextId contextId);

protected:
    virtual void InitVertexAttributeObjectStateForContext(ContextId contextId);
    void SetupVertexAttribute(const IVertexAttributeMappingPtr& shaderProgramAttributeMapping,
                              VertexLayout& vertexLayout, const VertexAttribute& vertexAttribute);

  void CreateVertexArrayObjectForContext(ContextId contextId);

  typedef std::map<ContextId, GLuint> VertexArrayIdList;
  VertexArrayIdList vertexArrayIds;
private:
    logging::GloveLogger logger;
};
}
} // namespace glove