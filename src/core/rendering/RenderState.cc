#include "RenderState.h"

namespace glove {

RenderState::RenderState(const glm::mat4& viewProjectionMatrix) : viewProjectionMatrix(viewProjectionMatrix) {

}

RenderState::RenderQueue& RenderState::GetRenderQueue() {
 return renderQueue;
}
}