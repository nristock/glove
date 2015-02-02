#pragma once

#include <GL/glew.h>
#include <GL/gl.h>

#include <glove/rendering/Rendering.h>
#include <glove/rendering/target/AbstractRenderTarget.h>

namespace glove {
namespace gl {

class GLRenderTarget : public AbstractRenderTarget {
  public:
    GLRenderTarget(const ScreenDimensions& targetDimensions);

    virtual const ScreenDimensions& GetDimensions() const;
    virtual void Bind();

private:
    GLuint framebufferId;
    GLuint targetTexture;
    ScreenDimensions targetDimensions;

};
}
}