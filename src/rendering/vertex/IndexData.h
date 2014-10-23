#pragma once

#include "core/GloveFwd.h"
#include "core/GloveObject.h"

namespace glove {

/**
* This class represents generic index data.
* It does not provider any read-back functionality. You can either use the buffer's read functions or ManagedIndexData.
*/
class IndexData : public GloveObject {
Profilable()
public:
    IndexData();

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
    virtual const GPUBufferPtr GetBuffer() const {
        return indexBuffer;
    }

protected:
    size_t indexCount;

    GPUBufferPtr indexBuffer;
};


} // namespace glove