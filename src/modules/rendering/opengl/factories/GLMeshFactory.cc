#include "factories/GLMeshFactory.hpp"
#include "subsystem/OpenGLRendererModule.hpp"
#include "GLMesh.hpp"

namespace glove {
namespace gl {

IMeshPtr GLMeshFactory::CreatedIndexedMesh(const IMaterialPtr& material, const IVertexDataPtr& vertexData,
                                           const IIndexDataPtr& indexData) {
    return GLMeshPtr(new GLMesh(material, vertexData, indexData));
}

IMeshPtr GLMeshFactory::CreateMesh(const IMaterialPtr& material, const IVertexDataPtr& vertexData) {
    return GLMeshPtr(new GLMesh(material, vertexData, IIndexDataPtr()));
}

IMeshPtr GLMeshFactory::CreateEmptyMesh(const IMaterialPtr& material) const {
    return GLMeshPtr(new GLMesh(material, IVertexDataPtr(), IIndexDataPtr()));
}
}
}