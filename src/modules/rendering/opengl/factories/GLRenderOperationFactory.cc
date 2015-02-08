#include <glove/rendering/IRenderOperation.h>
#include "factories/GLRenderOperationFactory.h"
#include "GLRenderOperation.h"

namespace glove {
namespace gl {

IRenderOperation* GLRenderOperationFactory::CreateRenderOperation(bool autoDelete) {
    return new GLRenderOperation(autoDelete);
}
}
}