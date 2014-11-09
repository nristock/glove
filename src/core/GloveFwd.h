#pragma once

#include <memory>

#define GLOVE_MAKE_SHARED(type_) typedef std::shared_ptr<type_>
#define GLOVE_FWD_DECL(type_)                    \
    class type_;                                \
    GLOVE_MAKE_SHARED(type_) type_##Pointer;    \
    GLOVE_MAKE_SHARED(type_) type_##Ptr;
#define GLOVE_FWD_DECL_STRUCT(type_)                    \
    struct type_;                                \
    GLOVE_MAKE_SHARED(type_) type_##Pointer;    \
    GLOVE_MAKE_SHARED(type_) type_##Ptr;

#if defined (DEBUG)
#define GLOVE_INLINE
#else
#define GLOVE_INLINE inline
#endif

namespace glove {

GLOVE_FWD_DECL(ShaderProgram);

GLOVE_FWD_DECL(IndexedMeshData);

GLOVE_FWD_DECL(MeshData);

GLOVE_FWD_DECL(IGpuBuffer);

GLOVE_FWD_DECL(GlovePythonEngine);

GLOVE_FWD_DECL(IWindow);
typedef IWindowPtr WindowPtr;

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

GLOVE_FWD_DECL(IRenderer);
typedef IRendererPtr RendererPtr;

GLOVE_FWD_DECL(Mesh);

GLOVE_FWD_DECL(IMesh);

GLOVE_FWD_DECL(PythonPlugin);

GLOVE_FWD_DECL(PythonScript);

GLOVE_FWD_DECL(GlovePlugin);

GLOVE_FWD_DECL(PluginLoader);

GLOVE_FWD_DECL_STRUCT(RenderOperation);
GLOVE_FWD_DECL_STRUCT(KeyEvent);

GLOVE_FWD_DECL(EventBus);

GLOVE_FWD_DECL(InputManager);

GLOVE_FWD_DECL(StringIdDatabase);

GLOVE_FWD_DECL(MemoryProfile);

GLOVE_FWD_DECL(IGpuBufferManager);
GLOVE_FWD_DECL(ISubsystemFactory);
GLOVE_FWD_DECL(ISharedLibraryLoader);
GLOVE_FWD_DECL(ISharedLibraryLoaderFactory);
class ISystemExtension;
typedef std::weak_ptr<ISystemExtension> ISystemExtensionPtr;
typedef std::shared_ptr<ISystemExtension> ISystemExtensionSharedPtr;

}
