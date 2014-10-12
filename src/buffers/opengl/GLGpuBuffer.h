#pragma once

#include <GL/glew.h>
#include <GL/gl.h>

#include "core/GloveObject.h"
#include "buffers/GPUBuffer.h"

namespace glove {

/** This class implements an GL hardware/GPU buffer */
class GLGpuBuffer : public GloveObject, public GPUBuffer {
	GLOVE_MEM_ALLOC_FUNCS("GLGpuBuffer")
public:
	GLGpuBuffer(BufferUsage usage, GLenum target);
	virtual ~GLGpuBuffer();

	virtual void Bind();
	virtual void Unbind();

	virtual void WriteData(size_t sizeInBytes, const void* data);

protected:
	/** Buffer object ID */
	GLuint bufferId;

	/** The buffer binding target */
	GLenum target;

	/** The buffer's intended usage */
	BufferUsage usage;
};


} // namespace glove