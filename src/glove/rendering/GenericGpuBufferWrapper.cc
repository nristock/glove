#include "GenericGpuBufferWrapper.hpp"
#include "RenderThread.hpp"

namespace glove {

GenericVertexBufferWrapper::GenericVertexBufferWrapper(const RenderResourceFactory& resourceFactory) {
    RenderDispatcher::EnsureRenderThread();

    vertexBuffer = resourceFactory.CreateVertexBuffer();
}

VertexBufferHandle GenericVertexBufferWrapper::GetHardwareResource() const {
    return vertexBuffer;
}

GenericIndexBufferWrapper::GenericIndexBufferWrapper(const RenderResourceFactory& resourceFactory) {
    RenderDispatcher::EnsureRenderThread();

    indexBuffer = resourceFactory.CreateIndexBuffer();
}

IndexBufferHandle GenericIndexBufferWrapper::GetHardwareResource() const {
    return indexBuffer;
}
}