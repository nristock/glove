#pragma once

#include <GL/glew.h>
#include <GL/gl.h>

#include <core/rendering/target/IRenderTarget.h>

namespace glove {
namespace gl {

class GLRenderTarget : public IRenderTarget {
  public:
    GLRenderTarget(const Dimensions& targetDimensions);

    virtual const Dimensions& GetDimensions() const;


    virtual void Bind();

private:
    GLuint framebufferId;
    GLuint targetTexture;
    Dimensions targetDimensions;
};
}
}