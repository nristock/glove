#include <boost/format.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glove/GloveException.h>

#include "shader/GLMaterial.h"
#include "shader/GLMaterialAttribute.h"
#include "shader/GLShaderProgram.h"

namespace {
const std::hash<std::string> g_stringHasher = std::hash<std::string>();

const std::size_t CalculateStringHash(const std::string& str) {
    return g_stringHasher(str);
}
}

namespace glove {
namespace gl {

GLMaterial::GLMaterial(const GLShaderProgramPtr& shader) : shader(shader) {
}

IShaderProgramPtr GLMaterial::GetShaderProgram() const {
    return shader;
}

IMaterialAttributePtr GLMaterial::GetMaterialAttribute(const std::string& name) {
    const std::size_t nameHash = CalculateStringHash(name);

    if(attributeNameMap.count(nameHash) > 0) {
        return attributeNameMap[nameHash];
    }

    auto materialAttribute = IMaterialAttributePtr(new GLMaterialAttribute(shader->GetUniformLocation(name), shared_from_this()));
    attributeNameMap.emplace(nameHash, materialAttribute);

    return materialAttribute;
}

IMaterialAttributePtr GLMaterial::GetMaterialAttribute(const MaterialAttributeSemantic semantic) {
    if(attributeSemanticMap.count(semantic) > 0) {
        return attributeSemanticMap[semantic];
    } else {
        throw GLOVE_EXCEPTION((boost::format("No material attribute mapped for %1%") % semantic).str());
    }
}

void GLMaterial::MapAttributeSemantic(const MaterialAttributeSemantic semantic, const std::string& attributeName) {
    attributeSemanticMap[semantic] = GetMaterialAttribute(attributeName);
}
}
} // namespace glove