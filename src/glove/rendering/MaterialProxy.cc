#include "glove/rendering/MaterialProxy.hpp"
#include "glove/rendering/RenderCommandList.hpp"
#include "glove/rendering/SceneView.hpp"
#include "glove/rendering/MeshBatch.hpp"

namespace glove {
void MaterialProxy::SetMesh(RenderCommandList& cmdList, const SceneView& view, const MeshBatchElement& mesh) {
    cmdList.EnableShaderProgram(GetShaderProgram());

    for(auto& parameter : uniformParameters) {
        parameter->Set(cmdList, view, mesh);
    }
}

void TextureUniformParameter::Set(RenderCommandList& cmdList, const SceneView& view, const MeshBatchElement& mesh) {
    cmdList.BindTexture2D(texture, slot);
    cmdList.SetIntUniform(uniformIndex, slot);
}
}