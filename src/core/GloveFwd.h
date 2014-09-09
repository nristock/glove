/*
 * GloveFwd.h
 *
 *  Created on: Aug 27, 2014
 *      Author: monofraps
 */

#ifndef GLOVEFWD_H_
#define GLOVEFWD_H_

#include <memory>

#define GLOVE_MAKE_SHARED(type_) typedef std::shared_ptr<type_>

namespace glove {

class ShaderProgram;
GLOVE_MAKE_SHARED(ShaderProgram) ShaderPointer;
GLOVE_MAKE_SHARED(ShaderProgram) ShaderPtr;

class IndexedMeshData;
GLOVE_MAKE_SHARED(IndexedMeshData) IndexedMeshDataPointer;
GLOVE_MAKE_SHARED(IndexedMeshData) IndexedMeshDataPtr;

class GloveRenderer;
GLOVE_MAKE_SHARED(GloveRenderer) GloveRendererPointer;
GLOVE_MAKE_SHARED(GloveRenderer) GloveRendererPtr;

class MeshData;
GLOVE_MAKE_SHARED(MeshData) MeshDataPointer;
GLOVE_MAKE_SHARED(MeshData) MeshDataPtr;

class GPUBuffer;
GLOVE_MAKE_SHARED(GPUBuffer) GPUBufferPointer;
GLOVE_MAKE_SHARED(GPUBuffer) GPUBufferPtr;

struct VertexLayoutAttribute;
GLOVE_MAKE_SHARED(VertexLayoutAttribute) VertexLayoutDefinitionPointer;
GLOVE_MAKE_SHARED(VertexLayoutAttribute) VertexLayoutDefinitionPtr;
GLOVE_MAKE_SHARED(VertexLayoutAttribute) VLDPtr;

class VertexAttributeBuffer;
GLOVE_MAKE_SHARED(VertexAttributeBuffer) VertexAttributeBufferPointer;
GLOVE_MAKE_SHARED(VertexAttributeBuffer) VertexAttributeBufferPtr;
GLOVE_MAKE_SHARED(VertexAttributeBuffer) VABPtr;

class GlovePythonEngine;
GLOVE_MAKE_SHARED(GlovePythonEngine) GlovePythonEnginePointer;
GLOVE_MAKE_SHARED(GlovePythonEngine) GlovePythonEnginePtr;

class GloveWindow;
GLOVE_MAKE_SHARED(GloveWindow) GloveWindowPointer;
GLOVE_MAKE_SHARED(GloveWindow) GloveWindowPtr;

class GlovePythonEngine;
GLOVE_MAKE_SHARED(GlovePythonEngine) GlovePythonEnginePointer;
GLOVE_MAKE_SHARED(GlovePythonEngine) GlovePythonEnginePtr;
}



#endif /* GLOVEFWD_H_ */
