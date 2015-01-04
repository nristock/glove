#include <core/rendering/IRenderOperation.h>
#include "GLRenderOperationFactory.h"
#include "../GLRenderOperation.h"

namespace glove {
namespace gl {

IRenderOperation* GLRenderOperationFactory::CreateRenderOperation(bool autoDelete) {
    return new GLRenderOperation(autoDelete);
}
}
}