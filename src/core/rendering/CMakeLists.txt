set(gc_rendering_src
   mesh/Mesh.cc

   vertex/IndexData.cc
   vertex/ManagedIndexData.cc
   vertex/VertexAttribute.cc
   vertex/VertexAttributeUtils.cc
   vertex/VertexData.cc
   vertex/VertexLayout.cc

   RenderOperation.cc
)

add_library(gc_rendering STATIC ${gc_rendering_src})