#pragma once

#include <GL/glew.h>
#include <map>

#include <pitamem/MemoryProfile.h>
#include <core/log/Log.h>
#include "shader/MappedMaterialAttribute.h"
#include <core/rendering/vertex/VertexAttributeSemantic.h>

namespace glove {

class ShaderProgram  {
Profilable();
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

    logging::GloveLogger logger;

    int numShaders;

    GLuint shaderProgramId;
    GLuint* shaderIds;

    VertexAttribMap vertexAttributeMap;
    MaterialAttributeMap materialAttributeMap;
};

} /* namespace glove */
