#include <glove/rendering/IRenderOperation.hpp>
#include "factories/GLRenderOperationFactory.hpp"
#include "GLRenderOperation.hpp"

namespace glove {
namespace gl {

IRenderOperation* GLRenderOperationFactory::CreateRenderOperation(bool autoDelete) {
    return new GLRenderOperation(autoDelete);
}
}
}