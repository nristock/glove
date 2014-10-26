#pragma once

#include "core/GloveFwd.h"
#include <pitamem/MemoryProfile.h>

namespace glove {

/**
* This class represents generic index data.
* It does not provider any read-back functionality. You can either use the buffer's read functions or ManagedIndexData.
*/
class IndexData  {
Profilable();
public:
	IndexData(const GpuBufferManagerPtr& gpuBufferManager);

    virtual ~IndexData();

    /** Returns the number of indices */
    virtual const size_t GetIndexCount() const {
        return indexCount;
    }

    /** Sets the number of indices */
    virtual void SetIndexCount(size_t count) {
        indexCount = count;
    }

    /** Returns the hardware/GPU buffer holding the index data */
	virtual const IGpuBufferPtr GetBuffer() const {
        return indexBuffer;
    }

protected:
    size_t indexCount;

	IGpuBufferPtr indexBuffer;
};


} // namespace glove