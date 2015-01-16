set(gc_graph_headers
   Graph.h
   GraphNode.h
   Scenegraph.h
   Transform.h

   gameobject/GameObject.h
   gameobject/factories/IGameObjectFactory.h
   gameobject/factories/EmptyGameObjectFactory.h

   gamecomponent/GameComponent.h
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