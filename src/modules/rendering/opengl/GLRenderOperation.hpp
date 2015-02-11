#pragma once

#include <glove/rendering/IRenderOperation.hpp>

#include "subsystem/OpenGLRendererModule.hpp"

namespace glove {
namespace gl {

class GLRenderOperation : public IRenderOperation {
public:
    GLRenderOperation(bool shouldDelete);

    virtual bool ShouldDelete() const;
    virtual void SetMesh(const IMeshPtr& mesh);
    virtual void Execute(const IRendererPtr& renderer);


    virtual void SetPreRenderUserCallback(PreRenderCallback callback);
    virtual void SetPostRenderUserCallback(PostRenderCallback callback);

protected:
    bool shouldDelete;
    GLMeshPtr glMesh;

    IRenderOperation::PreRenderCallback preRenderCallback;
    IRenderOperation::PostRenderCallback postRenderCallback;
};

}
}