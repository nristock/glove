#pragma once

#include <string>

#include <glm/glm.hpp>

#include "core/GloveFwd.h"
#include "core/GloveObject.h"
#include "MappedMaterialAttribute.h"

namespace glove {

class Material : public GloveObject {
Profilable()
public:
    Material(ShaderProgramPointer shader);

    virtual ~Material();

    void Enable() const;

    void Disable() const;

    void SetMaterialAttribute(MappedMaterialAttribute mappedAttribute, float& value);

    void SetMaterialAttribute(MappedMaterialAttribute mappedAttribute, glm::vec3& value);

    void SetMaterialAttribute(MappedMaterialAttribute mappedAttribute, glm::vec4& value);

    void SetMaterialAttribute(MappedMaterialAttribute mappedAttribute, glm::mat4& value);

    void PySetMaterialAttributeF(MappedMaterialAttribute mappedAttribute, float& value);

    void PySetMaterialAttributeV3(MappedMaterialAttribute mappedAttribute, glm::vec3& value);

    void PySetMaterialAttributeV4(MappedMaterialAttribute mappedAttribute, glm::vec4& value);

    void PySetMaterialAttributeMat4(MappedMaterialAttribute mappedAttribute, glm::mat4& value);

    ShaderProgramPointer GetShader() const {
        return shader;
    }

private:
    ShaderProgramPointer shader;
};


} // namespace glove