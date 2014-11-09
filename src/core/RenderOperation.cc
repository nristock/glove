#include "RenderOperation.h"

namespace glove {

RenderOperation::RenderOperation() : EnableProfilable() {

}

RenderOperation::~RenderOperation() {

}

void RenderOperation::Reset() {
    vertexData = nullptr;
    indexData = nullptr;
    material = nullptr;
}

} // namespace glove