#pragma once

#include <glove/rendering/Rendering.hpp>
#include <glove/rendering/target/AbstractRenderTarget.hpp>

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