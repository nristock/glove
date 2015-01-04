set(gc_graph_headers
   Graph.h
   GraphNode.h
   Scenegraph.h
   Transform.h

   gameobject/GameObject.h
   gameobject/factories/IGameObjectFactory.h
   gameobject/factories/EmptyGameObjectFactory.h

   gamecomponent/CameraBase.h
   gamecomponent/OrthoCamera.h
   gamecomponent/GameComponent.h
   gamecomponent/MeshRenderer.h
   gamecomponent/factories/CameraComponentFactory.h
)

set(gc_graph_src
   gamecomponent/CameraBase.cc
   gamecomponent/OrthoCamera.cc
   gamecomponent/GameComponent.cc
   gamecomponent/MeshRenderer.cc
   gamecomponent/factories/CameraComponentFactory.cc
   gameobject/factories/EmptyGameObjectFactory.cc
   gameobject/GameObject.cc
   GraphNode.cc
   Scenegraph.cc
   Transform.cc
)

add_library(gc_graph OBJECT ${gc_graph_src} ${gc_graph_headers})