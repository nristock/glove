/*
 * GPUBuffer.h
 *
 *  Created on: Aug 11, 2014
 *      Author: monofraps
 */

#ifndef GPUBUFFER_H_
#define GPUBUFFER_H_

#include <GL/glew.h>
#include <GL/gl.h>

#include "core/GloveObject.h"

namespace glove {

class GPUBuffer : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("GPUBuffer")
public:
	GPUBuffer(GLenum target, GLenum usage);
	virtual ~GPUBuffer();

	virtual void Bind();
	virtual void Unbind();

	void FillData(GLsizeiptr sizeInBytes, const GLvoid* data);

protected:
	GLenum target;
	GLenum usage;
	GLuint bufferId;
};

} /* namespace glove */

#endif /* GPUBUFFER_H_ */
