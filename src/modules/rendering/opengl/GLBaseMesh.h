#pragma once

#include <map>

#include <GL/glew.h>

#include <core/rendering/IRenderer.h>

#include "GLRenderer.h"
#include "internal/OpenGLWrapper.h"
#include "subsystem/OpenGLRendererModule.h"

namespace glove {
namespace gl {

/// @ingroup OpenGLRenderer
class GLBaseMesh {
  public:
    GLBaseMesh() = default;
    GLBaseMesh(const GLBaseMesh&) = delete;
    virtual ~GLBaseMesh();

    GLBaseMesh& operator=(const GLBaseMesh&) = delete;

    const GLuint GetVertexArrayId(ContextId contextId);
    void EnsureVertexArrayObjectExistsForContext(ContextId contextId);

  protected:
    typedef std::map<ContextId, GLuint> VertexArrayIdList;
    VertexArrayIdList vertexArrayIds;

    void CreateVertexArrayObjectForContext(ContextId contextId);
    virtual void InitVertexAttributeObjectStateForContext(ContextId contextId) = 0;
};
}
} // namespace glove