#pragma once

#include "GloveFwd.h"
#include <pitamem/MemoryProfile.h>

#include <rendering/buffers/BufferUsage.h>

namespace glove {

/**
* This class creates hardware/GPU buffers
* TODO: Split into interface and OGL implementation
*/
class GpuBufferManager  {
Profilable();
public:
	GpuBufferManager();

    virtual ~GpuBufferManager();

    /** Creates a vertex buffer */
	virtual IGpuBufferPtr CreateVertexBuffer(BufferUsage bufferUsage);

    /** Creates an index buffer */
	virtual IGpuBufferPtr CreateIndexBuffer();
};


} // namespace glove