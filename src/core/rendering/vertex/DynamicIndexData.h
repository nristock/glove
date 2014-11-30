#pragma once

#include <vector>

#include <core/GloveFwd.h>

#include "IIndexData.h"
#include "../Rendering.h"
#include "../buffers/IGpuBuffer.h"
#include "../factories/IGpuBufferFactory.h"

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

    virtual GLOVE_INLINE IndexList& GetIndices() { return indices; }

    /// @brief Sets the backing list of indices. This does not automatically sync the GPU buffer (See FlushBuffer())
    virtual GLOVE_INLINE void SetIndices(const IndexList& indexList) { indices = indexList; }

    virtual GLOVE_INLINE const size_t GetIndexCount() const { return indices.size(); }
    virtual GLOVE_INLINE const IGpuBufferPtr& GetGpuBuffer() const { return indexBuffer; }
    virtual GLOVE_INLINE void BindBuffer() { indexBuffer->Bind(); }

    /// @brief Uploads the backing data from RAM to the GPU.
    virtual GLOVE_INLINE void FlushBuffer() const {
        indexBuffer->WriteData(GetIndexCount() * sizeof(unsigned int), &indices[0]);
    }

  protected:
    IGpuBufferPtr indexBuffer;
    IndexList indices;
};

} // namespace glove