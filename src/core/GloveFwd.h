/*
 * GloveFwd.h
 *
 *  Created on: Aug 27, 2014
 *      Author: monofraps
 */

#ifndef GLOVEFWD_H_
#define GLOVEFWD_H_

#include <memory>

namespace glove {

class Shader;
typedef std::shared_ptr<Shader> ShaderPointer;
typedef ShaderPointer ShaderPtr;

class IndexedMeshData;
typedef std::shared_ptr<IndexedMeshData> IndexedMeshDataPointer;
typedef IndexedMeshDataPointer IndexedMeshDataPtr;

class GloveRenderer;
typedef std::shared_ptr<GloveRenderer> GloveRendererPointer;
typedef GloveRendererPointer GloveRendererPtr;

class MeshData;
typedef std::shared_ptr<MeshData> MeshDataPointer;
typedef MeshDataPointer MeshDataPtr;

class GPUBuffer;
typedef std::shared_ptr<GPUBuffer> GPUBufferPointer;
typedef GPUBufferPointer GPUBufferPtr;

struct VertexLayoutDefinition;
typedef std::shared_ptr<VertexLayoutDefinition> VertexLayoutDefinitionPointer;
typedef VertexLayoutDefinitionPointer VertexLayoutDefinitionPtr;
typedef VertexLayoutDefinitionPointer VLDPtr;

class VertexAttributeBuffer;
typedef std::shared_ptr<VertexAttributeBuffer> VertexAttributeBufferPointer;
typedef VertexAttributeBufferPointer VertexAttributeBufferPtr;
typedef VertexAttributeBufferPointer VABPtr;

class GlovePythonEngine;
typedef std::shared_ptr<GlovePythonEngine> GlovePythonEnginePointer;
typedef GlovePythonEnginePointer GlovePythonEnginePtr;
}



#endif /* GLOVEFWD_H_ */
