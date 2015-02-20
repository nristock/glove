#pragma once

#include <string>

#include "glove/rendering/Rendering.hpp"
#include "glove/services/Services.hpp"

namespace glove {

/// @ingroup RenderServices
class GLOVE_API_EXPORT IShaderFactory : public BasicService {
  public:
    static ServiceType serviceType;

    IShaderFactory() : BasicService(serviceType) {}
    virtual ~IShaderFactory(){};

    /// @brief Creates a vertex shader by loading it from the provided fileName.
    ///
    /// @param [in] fileName Path to the file containing the shader source.
    virtual IShaderPtr CreateVertexShader(std::string fileName) = 0;

    /// @brief Creates a fragment shader by loading it from the provided fileName.
    ///
    /// @param [in] fileName Path to the file containing the shader source.
    virtual IShaderPtr CreateFragmentShader(std::string fileName) = 0;
};
}