#pragma once

#include "glove/GloveFwd.hpp"
#include "glove/rendering/vertex/IIndexData.hpp"

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

    virtual const std::size_t GetIndexCount() const;
    virtual const IGpuBufferPtr& GetGpuBuffer() const;

    virtual void BindBuffer();

  protected:
    IGpuBufferPtr indexBuffer;
    size_t indexCount;
};

} // namespace glove