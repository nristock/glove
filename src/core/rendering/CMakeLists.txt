set(gc_rendering_src
   mesh/Mesh.cc

   vertex/StaticIndexData.cc
   vertex/StaticVertexData.cc
   vertex/VertexAttribute.cc
   vertex/VertexAttributeUtils.cc
   vertex/VertexLayout.cc

   WindowConstructionHints.cc

   IRenderSubsystem.cc
)

add_library(gc_rendering OBJECT ${gc_rendering_src})