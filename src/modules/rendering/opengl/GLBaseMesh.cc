#include "GLBaseMesh.h"

namespace glove {
namespace gl {

GLBaseMesh::~GLBaseMesh() {
    for (const std::pair<ContextId, GLuint>& vertexArrayIdContextMapping : vertexArrayIds) {
        GL::DeleteVertexArrays(1, &vertexArrayIdContextMapping.second);
    }
}

void GLBaseMesh::CreateVertexArrayObjectForContext(ContextId contextId) {
    if (vertexArrayIds.count(contextId)) {
        throw GLOVE_EXCEPTION("Cannot create multiple vertex array objects per mesh per context.")
    }

    GLuint temporaryId;
    GL::GenVertexArrays(1, &temporaryId);
    vertexArrayIds[contextId] = temporaryId;
}

const GLuint GLBaseMesh::GetVertexArrayId(ContextId contextId) {
    const GLuint vertexArrayObjectId = vertexArrayIds[contextId];
    return vertexArrayObjectId;
}

void GLBaseMesh::EnsureVertexArrayObjectExistsForContext(ContextId contextId) {
    if (vertexArrayIds.count(contextId)) {
        return;
    }

    CreateVertexArrayObjectForContext(contextId);
    InitVertexAttributeObjectStateForContext(contextId);
}

}
}