set(gc_input_headers
    InputAction.hpp

    events/KeyStateChanged.hpp
)

set(gc_input_src
   Keys.cc
   InputActionRegistry.cc
)

add_library(gc_input OBJECT ${gc_input_src} ${gc_input_headers})