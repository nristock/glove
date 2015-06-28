set(gc_world_headers
    component/EntityComponent.hpp
    component/WorldComponent.hpp
)

set(gc_world_src
    World.cc
    Transform.cc
    entity/Entity.cc
    scene/Scene.cc
    scene/SceneProxy.cc
)

add_library(gc_world OBJECT ${gc_world_src} ${gc_world_headers} )