#pragma once

#include <core/GloveFwd.h>
#include <core/pitamem/MemoryProfile.h>

namespace glove {

/**
* This class represents generic index data.
* It does not provider any read-back functionality. You can either use the buffer's read functions or ManagedIndexData.
*/
class IndexData {
    Profilable();

  public:
    IndexData(const IGpuBufferManagerPtr& gpuBufferManager);
    virtual ~IndexData();

    /** Returns the number of indices */
    virtual GLOVE_INLINE const size_t GetIndexCount() const;

    /** Sets the number of indices */
    virtual GLOVE_INLINE void SetIndexCount(size_t count);

    /** Returns the hardware/GPU buffer holding the index data */
    virtual GLOVE_INLINE const IGpuBufferPtr GetBuffer() const;

  protected:
    size_t indexCount;

    IGpuBufferPtr indexBuffer;
};

} // namespace glove