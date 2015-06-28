#pragma once

#include <vector>
#include <memory>

#include "glove/BlueDwarfApi.hpp"
#include "glove/rendering/RenderTarget.hpp"
#include "glove/rendering/Texture.hpp"
#include "glove/rendering/SceneView.hpp"
#include "glove/rendering/MeshBatch.hpp"

using namespace BlueDwarf;

namespace BlueDwarf {
class ShaderProgram;
class RenderCommandList;

/**
 * A uniform parameter of a ShaderProgram.
 */
class BD_API_EXPORT UniformParameter {
  public:
    using Handle = std::shared_ptr<UniformParameter>;

    /**
     * Rendering implementations identifier of a specific uniform parameter.
     */
    class UniformIndex {
      public:
        using Handle = std::shared_ptr<UniformIndex>;
        virtual ~UniformIndex() = default;

      protected:
        UniformIndex() = default;
    };

    UniformParameter(UniformIndex::Handle uniformIndex) : uniformIndex(uniformIndex) {}
    virtual ~UniformParameter() = default;

    virtual void Set(RenderCommandList& cmdList, const SceneView& view, const MeshBatchElement& mesh){};

  protected:
    UniformIndex::Handle uniformIndex;
};

/**
 * A UniformParameter representing a texture unit and sampler.
 */
class BD_API_EXPORT TextureUniformParameter : public UniformParameter {
  public:
    using Handle = std::shared_ptr<TextureUniformParameter>;

    TextureUniformParameter(const UniformIndex::Handle& uniformIndex, Texture2D::Handle texture)
        : UniformParameter(uniformIndex), texture(std::move(texture)), slot(0) {}

    void SetTexture(Texture2DHandle texture) { this->texture = texture; }
    void SetSlot(uint32 slot) { this->slot = slot; }

    virtual void Set(RenderCommandList& cmdList, const SceneView& view, const MeshBatchElement& mesh) override;

  protected:
    Texture2D::Handle texture;

    /// Texture unit slot to use.
    uint32 slot;
};

/**
 * The render threads representation of a Material.
 *
 * A MaterialProxy combines a ShaderProgram with @link UniformParameter UniformParameters @endlink. The parameter which
 * represents the shaders MVP uniform is helt separately.
 */
class BD_API_EXPORT MaterialProxy {
  public:
    void SetMesh(RenderCommandList& cmdList, const SceneView& view, const MeshBatchElement& mesh);

    Handle<ShaderProgram> GetShaderProgram() const { return shaderProgram; }

    MaterialProxy(Handle<ShaderProgram> shaderProgram, const std::vector<UniformParameter::Handle>& uniformParameters,
                  UniformParameter::Handle mvpParameter)
        : shaderProgram(shaderProgram), uniformParameters(uniformParameters), mvpParameter(std::move(mvpParameter)) {}
    MaterialProxy(Handle<ShaderProgram> shaderProgram, const std::vector<UniformParameter::Handle>& uniformParameters)
        : MaterialProxy(shaderProgram, uniformParameters, UniformParameter::Handle{new UniformParameter({})}) {}
    MaterialProxy(Handle<ShaderProgram> shaderProgram) : MaterialProxy(shaderProgram, {}) {}

  protected:
    Handle<ShaderProgram> shaderProgram;
    std::vector<UniformParameter::Handle> uniformParameters;
    UniformParameter::Handle mvpParameter;
};
}