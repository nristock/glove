#pragma once

#include <map>

#include <GL/glew.h>

#include "core/GloveFwd.h"
#include "core/IRenderer.h"
#include "rendering/opengl/GLRenderer.h"
#include "pitamem/MemoryProfile.h"

namespace glove {

class GLBaseMesh {
public:
    typedef std::map<size_t, GLuint> VertexArrayIdList;

    virtual ~GLBaseMesh() {
    };

    const GLuint GetVertexArrayId(size_t contextId) {
        return vertexArrayIds[contextId];
    }

    void AddVAO(size_t contextId, const RendererPtr& renderer) {
        std::shared_ptr<GLRenderer> glRenderer = std::dynamic_pointer_cast<GLRenderer>(renderer);

        vertexArrayIds[contextId] = glRenderer->GenerateVertexArray(contextId);
    }

protected:
    /** The Vertex Array Object ID */
    VertexArrayIdList vertexArrayIds;
};


} // namespace glove