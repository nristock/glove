#pragma once

#include <core/rendering/target/IRenderTarget.h>

namespace glove {
namespace gl {

class GLDefaultRenderTarget : public IRenderTarget {
  public:
    GLDefaultRenderTarget(const Dimensions& targetDimensions);

    virtual const Dimensions& GetDimensions() const;

    virtual void Bind();

private:
    Dimensions targetDimensions;
};

}
}