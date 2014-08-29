/*
 * Shader.h
 *
 *  Created on: Jul 29, 2014
 *      Author: monofraps
 */

#ifndef SHADER_H_
#define SHADER_H_

#include <GL/glew.h>
#include <map>

#include "core/GloveObject.h"

#define MVA_POSITIONS	0
#define MVA_COLORS		1

namespace glove {

class Shader : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("Shader")
public:
	Shader(int numShaders);
	virtual ~Shader();

	void AttachShader(int shaderId, GLenum shaderType, std::string fileName);
	void CreateProgram();

	void MapVertexAttribute(unsigned short attributeIdentifier, GLuint attribIndex);

	void Enable();
	void Disable();

	GLuint GetVertexAttributePosition(unsigned short attributeIdentifier);

private:
	typedef std::map<unsigned short, GLuint> VertexAttribMap;

	int numShaders;

	GLuint shaderProgramId;
	GLuint* shaderIds;

	VertexAttribMap vertexAttributeMap;
};

} /* namespace glove */

#endif /* SHADER_H_ */
