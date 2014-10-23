#pragma once

#include "core/GloveObject.h"
#include "core/GloveFwd.h"

#include "buffers/BufferUsage.h"

namespace glove {

/**
* This class creates hardware/GPU buffers
* TODO: Split into interface and OGL implementation
*/
class GpuBufferManager : public GloveObject {
Profilable()
public:
    GpuBufferManager();

    virtual ~GpuBufferManager();

    /** Creates a vertex buffer */
    virtual GPUBufferPtr CreateVertexBuffer(BufferUsage bufferUsage);

    /** Creates an index buffer */
    virtual GPUBufferPtr CreateIndexBuffer();
};


} // namespace glove