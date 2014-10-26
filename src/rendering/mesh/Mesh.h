#pragma once

#include "core/GloveFwd.h"

#include "graph/GameComponent.h"

#include "rendering/IRenderable.h"
#include "rendering/mesh/IMesh.h"

namespace glove {

/** Abstract mesh representation storing vertex, material and optional index data for passive rendering. */
class Mesh : public GameComponent, public IRenderable, public IMesh, public std::enable_shared_from_this<Mesh> {
Profilable()
public:
	Mesh(const RendererPtr& renderer, const GpuBufferManagerPtr gpuBufferManager, MaterialPtr material);

    virtual ~Mesh();

    virtual void Refresh();

    virtual const MaterialPtr& GetMaterial() const {
        return material;
    }

    virtual const VertexDataPtr& GetVertexData() const {
        return vertexData;
    }

    virtual const IndexDataPtr& GetIndexData() const {
        return indexData;
    }

    virtual const ShaderProgramPointer& GetShader() const {
        return shader;
    }

    virtual void SetupRender(RenderOperation& renderOp, const FrameData& frameData);

    virtual void PostRender(RenderOperation& renderOp, const FrameData& frameData) = 0;

    virtual void CreateIndexData();

protected:
    RendererPtr renderer;
    GpuBufferManagerPtr gpuBufferManager;

    VertexDataPtr vertexData;
    IndexDataPtr indexData;
    MaterialPtr material;
    ShaderProgramPointer shader;
};

} /* namespace glove */
