#pragma once

#include "../Rendering.h"

namespace glove {

/// @ingroup RenderSubsystemInterface
class IMaterial {
public:
    virtual ~IMaterial() = default;

    virtual IShaderProgramPtr GetShaderProgram() const = 0;
    virtual IMaterialAttributePtr GetMaterialAttribute(const std::string& name) = 0;
};

}