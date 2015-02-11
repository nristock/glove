#pragma once

#include <vector>

#include "glove/GloveFwd.hpp"
#include "glove/rendering/vertex/IIndexData.hpp"
#include "glove/rendering/Rendering.hpp"
#include "glove/rendering/buffers/IGpuBuffer.hpp"
#include "glove/rendering/factories/IGpuBufferFactory.hpp"

namespace glove {

/// @brief A class representing dynamic (writable) index data.
/// @ingroup RenderSubsystemInterface
///
/// This class has a backing std::vector keeping indices in RAM for easy read-back. It does also allow to modify the
/// data and upload it to the GPU.
template <typename IndexDataType> class DynamicIndexData : public IIndexData {
  public:
    typedef std::vector<IndexDataType> IndexList;

    /// @brief Creates an index GPU buffer using the provided IGpuBufferFactory.
    DynamicIndexData(const IGpuBufferFactoryPtr& gpuBufferFactory) {
        indexBuffer = gpuBufferFactory->CreateIndexBuffer();
    }

    virtual ~DynamicIndexData() = default;

    virtual IndexList& GetIndices() { return indices; }

    /// @brief Sets the backing list of indices. This does not automatically sync the GPU buffer (See FlushBuffer())
    virtual void SetIndices(const IndexList& indexList) { indices = indexList; }

    virtual const size_t GetIndexCount() const { return indices.size(); }
    virtual const IGpuBufferPtr& GetGpuBuffer() const { return indexBuffer; }
    virtual void BindBuffer() { indexBuffer->Bind(); }

    /// @brief Uploads the backing data from RAM to the GPU.
    virtual void FlushBuffer() const {
        indexBuffer->WriteData(GetIndexCount() * sizeof(unsigned int), &indices[0]);
    }

  protected:
    IGpuBufferPtr indexBuffer;
    IndexList indices;
};

} // namespace glove