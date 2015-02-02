#pragma once

#include <glove/rendering/factories/IRenderOperationFactory.h>

namespace glove {
namespace gl {
class GLRenderOperationFactory : public IRenderOperationFactory {
public:

    virtual IRenderOperation* CreateRenderOperation(bool autoDelete);
};
}
} /* namespace glove */