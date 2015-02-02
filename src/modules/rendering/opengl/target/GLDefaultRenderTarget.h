#pragma once

#include <glove/rendering/target/AbstractRenderTarget.h>
#include <glove/rendering/Rendering.h>

namespace glove {
namespace gl {

class GLDefaultRenderTarget : public AbstractRenderTarget {
  public:
    GLDefaultRenderTarget(const ScreenDimensions& targetDimensions);

    virtual const ScreenDimensions& GetDimensions() const;
    virtual void Bind();

private:
    ScreenDimensions targetDimensions;
};

}
}