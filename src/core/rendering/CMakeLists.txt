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

add_library(gc_rendering OBJECT ${gc_rendering_src})