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
#include <memory>

#define MVA_POSITIONS	0
#define MVA_COLORS		1

namespace glove {
namespace gl {
namespace shader {

class Shader {
public:
	Shader(int numShaders);
	virtual ~Shader();

	void AttachShader(int shaderId, GLenum shaderType, std::string fileName);
	void CreateProgram();

	void MapVertexAttribute(ushort attributeIdentifier, GLuint attribIndex);

	void Enable();
	void Disable();

	GLuint GetVertexAttributePosition(ushort attributeIdentifier);

private:
	typedef std::map<ushort, GLuint> VertexAttribMap;

	int numShaders;

	GLuint shaderProgramId;
	GLuint* shaderIds;

	VertexAttribMap vertexAttributeMap;
};

typedef std::shared_ptr<Shader> ShaderPtr;

} /* namespace shader */
} /* namespace gl */
} /* namespace glove */

#endif /* SHADER_H_ */
