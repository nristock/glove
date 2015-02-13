set(gc_rendering_headers
    buffers/BufferUsage.hpp
    buffers/IGpuBuffer.hpp

    factories/IGpuBufferFactory.hpp
    factories/IMaterialFactory.hpp
    factories/IMeshFactory.hpp
    factories/IRendererFactory.hpp
    factories/IRenderOperationFactory.hpp
    factories/IShaderFactory.hpp
    factories/IShaderProgramFactory.hpp
    factories/TextureFactory.hpp

    mesh/IMesh.hpp

    shader/IMaterial.hpp
    shader/IMaterialAttribute.hpp
    shader/IShader.hpp
    shader/IShaderProgram.hpp
    shader/MaterialTextureAttribute.hpp

    target/IRenderTarget.hpp

    vertex/DynamicIndexData.hpp
    vertex/DynamicVertexData.hpp
    vertex/IIndexData.hpp
    vertex/IVertexAttributeMapping.hpp
    vertex/IVertexData.hpp
    vertex/VertexAttributeSemantic.hpp
    vertex/VertexAttributeType.hpp
    vertex/VertexLayouts.hpp

    texture/Texture.cc

    FrameData.hpp
    IRenderer.hpp
    IRenderOperation.hpp
    IWindow.hpp
    Rendering.hpp
    RenderingInterfaces.hpp
    RenderOperation.hpp
)

set(gc_rendering_src
   mesh/Mesh.cc

   vertex/StaticIndexData.cc
   vertex/StaticVertexData.cc
   vertex/VertexAttribute.cc
   vertex/VertexAttributeUtils.cc
   vertex/VertexLayout.cc

   gamecomponent/CameraBase.cc
   gamecomponent/MeshRenderer.cc
   gamecomponent/OrthoCamera.cc

   gamecomponent/factories/CameraComponentFactory.cc

   target/AbstractRenderTarget.cc

   shader/MaterialAttributeSemantic.cc

   WindowConstructionHints.cc
   RenderState.cc
   RendererBase.cc

   IRenderSubsystem.cc
)

add_library(gc_rendering OBJECT ${gc_rendering_src} ${gc_rendering_headers})