set(gc_graph_src
   Camera.cc
   GameComponent.cc
   GameObject.cc
   IGraphNode.cc
   Scenegraph.cc
   Transform.cc
)

add_library(gc_graph STATIC ${gc_graph_src})