#include <boost/format.hpp>

#include <glove/GloveException.h>
#include <glove/utils/ShaderUtils.h>

#include "shader/GLShaderProgram.h"
#include "shader/GLShader.h"
#include "shader/GLVertexAttributeMapping.h"
#include "internal/OpenGLWrapper.h"

namespace glove {
namespace gl {

GLShaderProgram::GLShaderProgram(const std::list<IShaderPtr>& shaders) {
    for (const IShaderPtr& shader : shaders) {
        GLShaderPtr glShader = std::dynamic_pointer_cast<GLShader>(shader);
        this->shaders.push_back(glShader);
    }

    shaderProgramId = GL::CreateProgram();
    for (const GLShaderPtr& shader : this->shaders) {
        GL::AttachShader(shaderProgramId, shader->GetGLShaderId());
    }

    GL::LinkProgram(shaderProgramId);

    GLint linkStatus;
    GL::GetProgramiv(shaderProgramId, GL_LINK_STATUS, &linkStatus);

    if (linkStatus == GL_FALSE) {
        GL::DeleteProgram(shaderProgramId);
        PrintShaderProgramLinkLog(shaderProgramId);
        throw GLOVE_EXCEPTION("Failed to link shader program");
    }

    vertexAttributeMapping = IVertexAttributeMappingPtr(new GLVertexAttributeMapping());
}

GLShaderProgram::~GLShaderProgram() {
    GL::DeleteProgram(shaderProgramId);
}

GLint GLShaderProgram::GetUniformLocation(const std::string& uniformName) {
    GLint uniformIndex = GL::GetUniformLocation(shaderProgramId, uniformName.c_str());
    if (uniformIndex < 0) {
        throw GLOVE_EXCEPTION((boost::format("Unknown uniform attribute name %1%") % uniformName).str())
    }

    return uniformIndex;
}

GLint GLShaderProgram::GetVertexAttributeLocation(const std::string& attributeName) {
    GLint attributeIndex = GL::GetAttribLocation(shaderProgramId, attributeName.c_str());
    if (attributeIndex < 0) {
        LOG(logger, error, "Unknown vertex attribute name " << attributeName);
        return -1;
    }

    return attributeIndex;
}

IVertexAttributeMappingPtr GLShaderProgram::GetVertexAttributeMapping() {
    return vertexAttributeMapping;
}

void GLShaderProgram::Enable() {
    glUseProgram(shaderProgramId);
}

void GLShaderProgram::Disable() {
    GL::UseProgram(0);
}
}
} /* namespace glove */
