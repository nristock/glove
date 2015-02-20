#pragma once

#include "glove/rendering/Rendering.hpp"
#include "glove/rendering/buffers/BufferUsage.hpp"
#include "glove/services/Services.hpp"

namespace glove {

/// @ingroup RenderServices
class GLOVE_API_EXPORT IGpuBufferFactory : public BasicService {
  public:
    static ServiceType serviceType;

    IGpuBufferFactory() : BasicService(serviceType) {}
    virtual ~IGpuBufferFactory(){};

    virtual IGpuBufferPtr CreateVertexBuffer(BufferUsage bufferUsage) const = 0;
    virtual IGpuBufferPtr CreateIndexBuffer() const = 0;
};
}