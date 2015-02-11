#pragma once

#include <glove/rendering/factories/IGpuBufferFactory.hpp>

namespace glove {
namespace gl {

/// @ingroup Factories
class GLGpuBufferFactory : public IGpuBufferFactory {
  private:
    virtual IGpuBufferPtr CreateVertexBuffer(BufferUsage bufferUsage) const;
    virtual IGpuBufferPtr CreateIndexBuffer() const;
};
}
} /* namespace glove */