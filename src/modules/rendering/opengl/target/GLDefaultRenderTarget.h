#pragma once

#include <core/rendering/target/AbstractRenderTarget.h>
#include <core/rendering/Rendering.h>

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