#pragma once

#include <string>

#include <glm/glm.hpp>

#include "core/GloveFwd.h"
#include <pitamem/MemoryProfile.h>
#include <log/Log.h>
#include "MappedMaterialAttribute.h"

namespace glove {

class Material {
Profilable();
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
    logging::GloveLogger logger;

    ShaderProgramPointer shader;
};


} // namespace glove