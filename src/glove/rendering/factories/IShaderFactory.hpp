#pragma once

#include <string>

#include "glove/rendering/Rendering.hpp"

namespace glove {

/// @ingroup RenderSubsystemInterface
class IShaderFactory {
  public:
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