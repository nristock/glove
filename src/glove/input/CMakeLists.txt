set(gc_input_headers
    events/KeyStateChanged.hpp
)

set(gc_input_src
   Keys.cc
)

add_library(gc_input OBJECT ${gc_input_src} ${gc_input_headers})