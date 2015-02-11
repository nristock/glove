#pragma once

#include <glove/rendering/factories/IRenderOperationFactory.hpp>

namespace glove {
namespace gl {
class GLRenderOperationFactory : public IRenderOperationFactory {
public:

    virtual IRenderOperation* CreateRenderOperation(bool autoDelete);
};
}
} /* namespace glove */