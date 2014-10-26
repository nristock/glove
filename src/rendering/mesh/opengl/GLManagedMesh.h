#pragma once

#include <GL/glew.h>
#include <GL/gl.h>

#include "rendering/mesh/ManagedMesh.h"
#include "rendering/mesh/opengl/GLBaseMesh.h"

GLEWContext* glewGetContext();

namespace glove {

template<class VertexLayoutType>
class GLManagedMesh : public ManagedMesh<VertexLayoutType>, public GLBaseMesh {
Profilable()
public:
	GLManagedMesh(const RendererPtr& renderer, const GpuBufferManagerPtr& gpuBufferManager, MaterialPtr material) :
            ManagedMesh<VertexLayoutType>(renderer, gpuBufferManager, material),
            EnableProfilable() {
        glRenderer = std::dynamic_pointer_cast<GLRenderer>(renderer);
    }

    virtual ~GLManagedMesh() {
        for (auto vertexArrayIdEntry : vertexArrayIds) {
            glRenderer->DestroyVertexArray(vertexArrayIdEntry.first, vertexArrayIdEntry.second);
        }
    }

    virtual void SetupRender(RenderOperation& renderOp, const FrameData& frameData) {
        glGetError();

        ManagedMesh<VertexLayoutType>::SetupRender(renderOp, frameData);

        glBindVertexArray(GetVertexArrayId(frameData.currentContext));

        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            LOG(logger, error, error);
        }
    }

    virtual void PostRender(RenderOperation& renderOp, const FrameData& frameData) {
    }

private:
    logging::GloveLogger logger;

    std::shared_ptr<GLRenderer> glRenderer;
};


} // namespace glove