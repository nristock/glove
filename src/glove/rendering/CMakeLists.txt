set(gc_rendering_headers
    VertexLayout.hpp
    GpuBuffer.hpp
    SceneRenderer.hpp
    RenderHardwareCommands.hpp
    RenderHardwareInterface.hpp
    RenderResourceFactory.hpp
    Texture.hpp
    Material.hpp
    Shader.hpp
    WindowFactoryService.hpp
    RendererService.hpp
)

set(gc_rendering_src
    SceneView.cc
    VertexBindingFactory.cc
    ForwardSceneRenderer.cc
    VertexBinding.cc
    RenderCommandList.cc
    MeshBatch.cc
    ApplicationViewport.cc
    PrimitiveDrawInterface.cc
    MaterialProxy.cc
    RenderThread.cc
    Services.cc
    PrimitiveDrawUtils.cc
    GenericGpuBufferWrapper.cc
    ShaderParameter.cc
    material/MaterialLoader.cc
)

add_library(gc_rendering OBJECT ${gc_rendering_src} ${gc_rendering_headers} )