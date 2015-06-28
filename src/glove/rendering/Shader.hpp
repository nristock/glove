#pragma once

#include "glove/GloveApi.hpp"
#include "glove/rendering/ShaderParameter.hpp"
#include "glove/rendering/MaterialProxy.hpp"

namespace glove {

class GLOVE_API_EXPORT VertexShader : public RenderHardwareResource {
  public:
    using Handle = std::shared_ptr<VertexShader>;

    virtual ~VertexShader() = default;

    virtual const ShaderParameterMap& GetParameterMap() { return shaderParameters; }

  protected:
    VertexShader(const ShaderParameterMap& shaderParameterMap) : shaderParameters(shaderParameterMap) {}

    ShaderParameterMap shaderParameters;
};

class GLOVE_API_EXPORT FragmentShader : public RenderHardwareResource {
  public:
    using Handle = std::shared_ptr<FragmentShader>;

    virtual ~FragmentShader() = default;
};

class GLOVE_API_EXPORT ShaderProgram {
  public:
    using Handle = std::shared_ptr<ShaderProgram>;

    virtual ~ShaderProgram() = default;

    VertexShader::Handle GetVertexShader() const { return vertexShader; }
    FragmentShader::Handle GetFragmentShader() const { return fragmentShader; }

    virtual UniformParameter::UniformIndex::Handle GetUniformParameterIndex(const std::string& uniformName) = 0;

  protected:
    ShaderProgram(VertexShader::Handle vertexShader, FragmentShader::Handle fragmentShader)
        : vertexShader(vertexShader), fragmentShader(fragmentShader) {}

    VertexShader::Handle vertexShader;
    FragmentShader::Handle fragmentShader;
};
}