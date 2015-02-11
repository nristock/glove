#pragma once

#include <vector>

#include "glove/GloveFwd.hpp"
#include "glove/GloveCore.hpp"
#include "glove/rendering/vertex/IVertexData.hpp"
#include "glove/rendering/vertex/VertexLayout.hpp"
#include "glove/rendering/vertex/VertexAttribute.hpp"
#include "glove/rendering/factories/IGpuBufferFactory.hpp"
#include "glove/rendering/buffers/IGpuBuffer.hpp"
#include "glove/rendering/buffers/BufferUsage.hpp"

namespace glove {

/// @brief A class representing dynamic (writable) vertex data.
/// @ingroup RenderSubsystemInterface
///
/// This class has a backing std::vector keeping vertex data in RAM for easy read-back. It does also allow to modify
/// the data and upload it to the GPU. DynamicVertexData only supports a single IGpuBuffer at the moment. (todo)
template <class VertexDataType> class GLOVE_API_EXPORT DynamicVertexData : public IVertexData {
  public:
    typedef std::vector<VertexDataType> VertexList;

    /// @brief Calls DynamicVertexData(const IGpuBufferFactoryPtr& gpuBufferFactory, const VertexLayout& vertexLayout,
    ///        BufferUsage defaultBufferUsage) with defaultBufferUsage set to STATIC.
    /// The implicitly created GPU buffer will not be optimized for dynamic data writes.
    DynamicVertexData(const IGpuBufferFactoryPtr& gpuBufferFactory, const VertexLayout& vertexLayout)
        : DynamicVertexData(gpuBufferFactory, vertexLayout, BufferUsage::STATIC) {}

    /// @brief Creates a GPU buffer with the provided defaultBufferUsage.
    ///
    /// Will also perform a consistency check on the provided vertexLayout and copy-construct it to
    /// DynamicVertexData::vertexLayout.
    DynamicVertexData(const IGpuBufferFactoryPtr& gpuBufferFactory, const VertexLayout& vertexLayout,
                      BufferUsage defaultBufferUsage)
        : vertexLayout(vertexLayout) {

        CheckVertexLayoutConsistency();
        vertexBuffer = gpuBufferFactory->CreateVertexBuffer(defaultBufferUsage);
    }

    /// @brief Create a DynamicVertexData instance from an existing GPU buffer and vertex layout.
    ///
    /// Will also perform a consistency check on the provided vertexLayout and copy-construct it to
    /// DynamicVertexData::vertexLayout.
    DynamicVertexData(const IGpuBufferPtr& gpuBuffer, const VertexLayout& vertexLayout)
        : vertexBuffer(gpuBuffer), vertexLayout(vertexLayout) {
        CheckVertexLayoutConsistency();
    }

    virtual ~DynamicVertexData() = default;

    virtual VertexList& GetVertices() { return vertices; }

    /// @brief Sets the internal list of vertices. This does not automatically sync the GPU buffer (See FlushBuffer())
    virtual void SetVertices(const VertexList& vertexList) { vertices = vertexList; }

    virtual const std::size_t GetVertexCount() const { return vertices.size(); }
    virtual const std::size_t GetGpuBufferCount() const { return 1; }

    virtual const IGpuBufferPtr& GetGpuBuffer(std::size_t bufferIndex) const {
        // todo allow more than 1 gpu buffer
        if (bufferIndex != 0) {
            throw GLOVE_EXCEPTION("Buffer index out of range.");
        }
        return vertexBuffer;
    }

    virtual const VertexLayout& GetVertexLayout() const { return vertexLayout; }

    /// @brief Uploads the backing data from RAM to the GPU.
    virtual void FlushBuffer() {
        vertexBuffer->WriteData(sizeof(VertexDataType) * GetVertexCount(), &vertices[0]);
    }

    virtual void BindAllBuffers() { vertexBuffer->Bind(); }

  protected:
    IGpuBufferPtr vertexBuffer;
    VertexLayout vertexLayout;

    VertexList vertices;

    /// @brief DynamicVertexData<T> currently only supports a single GPU buffer so make sure the provided vertex layout
    ///        doesn't specify more than one (i.e. the highest GPU buffer index is 0)
    void CheckVertexLayoutConsistency() const {
        for (std::size_t i = 0; i < vertexLayout.GetAttributeCount(); ++i) {
            const VertexAttribute& attribute = vertexLayout.GetAttribute(i);
            if (attribute.GetBufferIndex() > 0) {
                throw GLOVE_EXCEPTION("DynamicVertexData<T> only supports a single GPU buffer but provided "
                                      "vertexLayout defines at least two different buffer indices.")
            }
        }
    }
};

} // namespace glove