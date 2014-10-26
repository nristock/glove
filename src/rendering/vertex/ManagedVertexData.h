#pragma once

#include <vector>

#include "core/GloveFwd.h"
#include "core/GloveCore.h"
#include "core/GpuBufferManager.h"

#include "buffers/IGpuBuffer.h"
#include "rendering/vertex/VertexData.h"

namespace glove {

/**
* A class representing "managed" vertex data.
* This class can be used to simplify working with pre defined vertex layouts in rendering/vertex/VertexLayouts.h.
* It furthermore introduces an additional copy of vertex data in RAM for fast read-backs.
*/
template<class VertexLayoutType>
class ManagedVertexData : public VertexData {
Profilable()
public:
    /** The type of the vertex list */
    typedef std::vector<VertexLayoutType> VertexList;

	ManagedVertexData(const GpuBufferManagerPtr& gpuBufferManager);

    virtual ~ManagedVertexData() {

    }

    /** Returns the internal list of vertices from RAM */
    virtual const VertexList& GetVertices() {
        return vertices;
    }

    /** Sets the internal list of vertices. This does not automatically sync the GPU buffer (See FlushBuffer()) */
    virtual void SetVertices(VertexList vertexList) {
        vertices = vertexList;
    }

    /** Returns the number of vertices in the RAM buffer */
    virtual size_t GetVertexCount() const {
        return vertices.size();
    }

    /** NoOp */
    virtual void SetVertexCount(size_t vertexCount) {
    }

    /** Uploads the RAM buffer to the GPU */
    virtual void FlushBuffer() {
        GetBuffer(0)->WriteData(sizeof(VertexLayoutType) * GetVertexCount(), &vertices[0]);
    }

protected:
    VertexList vertices;

private:
    GpuBufferManagerPtr gpuBufferManager;

    /** Creates the GPU buffers */
    virtual void CreateBuffers() {
        // TODO: expose buffer usage, allow multiple buffers
        IGpuBufferPtr vbuf = gpuBufferManager->CreateVertexBuffer(BU_STATIC);
        SetBufferBinding(0, vbuf);
    }
};


} // namespace glove