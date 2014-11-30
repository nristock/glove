#pragma once

#include <core/GloveFwd.h>

#include "IIndexData.h"

namespace glove {

/// @brief Represents static (non-modifiable) index data.
/// @ingroup RenderSubsystemInterface
///
/// While it is still possible to modify the buffer's data by invoking the buffer API directly it is *not* possible to
/// change StaticIndexData::indexCount once created. See DynamicIndexData if you need to modify your data.
class StaticIndexData : public IIndexData {
  public:
    StaticIndexData(const IGpuBufferPtr& indexBuffer, std::size_t numIndices);
    virtual ~StaticIndexData() = default;

    virtual GLOVE_INLINE const std::size_t GetIndexCount() const;
    virtual GLOVE_INLINE const IGpuBufferPtr& GetGpuBuffer() const;

    virtual GLOVE_INLINE void BindBuffer();

protected:
    IGpuBufferPtr indexBuffer;
    size_t indexCount;
};

} // namespace glove