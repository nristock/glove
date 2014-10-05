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
#define GLOVE_FWD_DECL(type_)					\
	class type_;								\
	GLOVE_MAKE_SHARED(type_) type_##Pointer;	\
	GLOVE_MAKE_SHARED(type_) type_##Ptr;
#define GLOVE_FWD_DECL_STRUCT(type_)					\
	struct type_;								\
	GLOVE_MAKE_SHARED(type_) type_##Pointer;	\
	GLOVE_MAKE_SHARED(type_) type_##Ptr;

namespace glove {

GLOVE_FWD_DECL(ShaderProgram);

GLOVE_FWD_DECL(IndexedMeshData);

GLOVE_FWD_DECL(GloveRenderer);

GLOVE_FWD_DECL(MeshData);

GLOVE_FWD_DECL(GPUBuffer);

GLOVE_FWD_DECL(GlovePythonEngine);

GLOVE_FWD_DECL(GloveWindow);

GLOVE_FWD_DECL(GlovePythonEngine);

GLOVE_FWD_DECL(PyShedLoader);

GLOVE_FWD_DECL(Material);

GLOVE_FWD_DECL(GameObject);

GLOVE_FWD_DECL(Camera);

GLOVE_FWD_DECL(Scenegraph);

GLOVE_FWD_DECL(GloveCore);

GLOVE_FWD_DECL(IRenderable);

GLOVE_FWD_DECL(GameComponent);

GLOVE_FWD_DECL(IGraphNode);

GLOVE_FWD_DECL(IGameComponentFactory);

GLOVE_FWD_DECL(VertexLayout);

GLOVE_FWD_DECL(VertexData);

GLOVE_FWD_DECL(IndexData);

GLOVE_FWD_DECL(ManagedIndexData);

GLOVE_FWD_DECL(GpuBufferManager);

GLOVE_FWD_DECL(Renderer);

GLOVE_FWD_DECL(Mesh);

GLOVE_FWD_DECL(IMesh);

GLOVE_FWD_DECL(PythonPlugin);

GLOVE_FWD_DECL(PythonScript);

GLOVE_FWD_DECL(GlovePlugin);

GLOVE_FWD_DECL(PluginLoader);

GLOVE_FWD_DECL_STRUCT(RenderOperation);
GLOVE_FWD_DECL_STRUCT(KeyEvent);

GLOVE_FWD_DECL(EventSubscriber);
GLOVE_FWD_DECL(EventBus);
GLOVE_FWD_DECL(InputManager);

}



#endif /* GLOVEFWD_H_ */
