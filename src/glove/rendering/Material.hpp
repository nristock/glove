#pragma once

#include <memory>

#include "glove/GloveApi.hpp"

namespace glove {
class ShaderProgram;
using ShaderProgramHandle = std::shared_ptr<ShaderProgram>;

class RenderCommandList;
struct SceneView;

class MaterialProxy;
using MaterialProxyHandle = std::shared_ptr<MaterialProxy>;

class GLOVE_API_EXPORT Material {
  public:
    using Handle = std::shared_ptr<Material>;

    virtual ~Material() = default;

    virtual MaterialProxyHandle CreateRenderProxy() = 0;

  protected:
    Material(ShaderProgramHandle shaderProgram) : shaderProgram(shaderProgram) {}

    ShaderProgramHandle shaderProgram;
};

class GLOVE_API_EXPORT BasicMaterial : public Material {
  public:
    BasicMaterial(const ShaderProgramHandle& shaderProgram) : Material(shaderProgram) { }


    virtual MaterialProxyHandle CreateRenderProxy() {
        return std::make_shared<MaterialProxy>(shaderProgram);
    };
};
}