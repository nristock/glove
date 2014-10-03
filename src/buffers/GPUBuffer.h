#ifndef BUFFERS_GPUBUFFER_H_
#define BUFFERS_GPUBUFFER_H_

#include "core/GloveObject.h"

#include "buffers/BufferUsage.h"

namespace glove {

/** A class abstracting hardware/GPU buffers */
class GPUBuffer : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("GPUBuffer")
public:
	GPUBuffer(BufferUsage usage);
	virtual ~GPUBuffer();

	/** Binds the buffer for use. Can be called mutiple times per frame. */
	virtual void Bind() = 0;

	/** Unbinds the buffer. Can be called mutiple times per frame. */
	virtual void Unbind() = 0;

	/** Writes data to the buffer and uploads it to the GPU */
	virtual void WriteData(size_t sizeInBytes, const void* data) = 0;

protected:
	/** The buffer's intended usage */
	BufferUsage usage;
};

} /* namespace glove */

#endif /* BUFFERS_GPUBUFFER_H_ */
