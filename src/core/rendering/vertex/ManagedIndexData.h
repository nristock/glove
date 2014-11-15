#pragma once

#include <vector>

#include <core/rendering/vertex/IndexData.h>

namespace glove {

/**
* Represents managed index data.
* This class adds and additional RAM buffer for indices for fast and easy read-backs.
*/
class ManagedIndexData : public IndexData {
    Profilable()
  public:
    /** The index list type */
    typedef std::vector<unsigned int> IndexList;

    ManagedIndexData(const IGpuBufferManagerPtr& gpuBufferManager);

    virtual ~ManagedIndexData();

    /** Returns the internal (RAM) list of indices */
    virtual const IndexList& GetIndices() const { return indices; }

    /** Sets the internal (RAM) list of indices but does not automatically update the GPU buffer */
    virtual void SetIndices(IndexList indexList) { indices = indexList; }

    /** Returns the number of indices in the RAM buffer */
    virtual const size_t GetIndexCount() const { return indices.size(); }

    /** NoOp */
    virtual void SetIndexCount(size_t count) {}

    /** Uploads the RAM buffer to the GPU */
    virtual void FlushBuffer() const;

  protected:
    IndexList indices;
};

} // namespace glove