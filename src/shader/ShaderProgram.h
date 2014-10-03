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
#include "shader/MappedMaterialAttribute.h"
#include "rendering/vertex/VertexAttributeSemantic.h"

namespace glove {

class ShaderProgram : public GloveObject {
	GLOVE_MEM_ALLOC_FUNCS("ShaderProgram")
public:
	ShaderProgram();
	ShaderProgram(int numShaders);
	virtual ~ShaderProgram();
	
	void LoadShader(int shaderId, GLenum shaderType, std::string& fileName);
	void LoadVertexShader(std::string fileName);
	void LoadFragmentShader(std::string fileName);
	
	void CreateProgram();

	void MapVertexAttribute(VertexAttributeSemantic attributeSemantic, std::string attribName);
	void MapMaterialAttribute(MappedMaterialAttribute attributeIdentifier, std::string attribname);

	void Enable();
	void Disable();

	void SetShader(int programSlot, GLuint ProgramId);

	GLuint GetVertexAttributePosition(VertexAttributeSemantic attributeSemantic);
	GLuint GetMaterialAttributePosition(MappedMaterialAttribute attributeIdentifier);

private:
	typedef std::map<VertexAttributeSemantic, GLuint> VertexAttribMap;
	typedef std::map<MappedMaterialAttribute, GLuint> MaterialAttributeMap;

	int numShaders;

	GLuint shaderProgramId;
	GLuint* shaderIds;

	VertexAttribMap vertexAttributeMap;
	MaterialAttributeMap materialAttributeMap;
};

} /* namespace glove */

#endif /* SHADER_H_ */
