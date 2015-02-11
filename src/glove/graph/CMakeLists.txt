set(gc_graph_headers
   gameobject/factories/IGameObjectFactory.hpp

   Graph.hpp
)

set(gc_graph_src
   gamecomponent/GameComponent.cc
   gameobject/factories/EmptyGameObjectFactory.cc
   gameobject/GameObject.cc
   GraphNode.cc
   Scenegraph.cc
   Transform.cc
)

add_library(gc_graph OBJECT ${gc_graph_src} ${gc_graph_headers})