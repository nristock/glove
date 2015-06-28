#pragma once

#include "glove/BlueDwarfApi.hpp"
#include "glove/CommonTypes.hpp"

#include "glove/rendering/RenderHardwareResource.hpp"

namespace BlueDwarf {

/// Access modes which can be used by the rendering implementation to optimize buffer client memory mapping.
enum class BufferMappingMode : uint8 { ReadOnly, WriteOnly, ReadWrite };

/**
* This class represents a GPU buffer resource designated to holding vertices. Details are up to the renderer
* implementation.
*
* Instances of this class should only be created through the renderer interface.
*/
class BD_API_EXPORT VertexBuffer : public RenderHardwareResource {
  public:
    virtual ~VertexBuffer() = default;

    /// Maps the VertexBuffer object into client memory so it can be read from and/or written to.
    virtual void* Map(BufferMappingMode mapMode) = 0;

    /// Flushes any changes in client memory to the GPU and unmaps the VertexBuffer.
    virtual void Unmap() = 0;

    /// Copies @p sizeInBytes amount of bytes from @p data to the GPU buffer.
    virtual void Store(std::size_t sizeInBytes, void* data) = 0;

  protected:
    /// Do not create an instance of this class directly. Use the RenderResourceFactory.
    VertexBuffer() = default;
};

/**
* This class represents a GPU buffer resource designated to holding indices. Details are up to the renderer
* implementation
*
* Instances of this class should only be created through the renderer interface.
*/
class BD_API_EXPORT IndexBuffer : public RenderHardwareResource {
  public:
    virtual ~IndexBuffer() = default;

    /// Maps the IndexBuffer object into client memory so it can be read from and/or written to.
    virtual void* Map(BufferMappingMode mapMode) = 0;

    /// Flushes any changes in client memory to the GPU and unmaps the IndexBuffer.
    virtual void Unmap() = 0;

    /// Copies @p sizeInBytes amount of bytes from @p data to the GPU buffer.
    virtual void Store(std::size_t sizeInBytes, void* data) = 0;

  protected:
    /// Do not create an instance of this class directly. Use the RenderResourceFactory.
    IndexBuffer() = default;
};

} /* namespace BlueDwarf */