set(gc_input_src
   InputManager.cc
)

add_library(gc_input STATIC ${gc_input_src})
target_link_libraries(gc_input gc_events)