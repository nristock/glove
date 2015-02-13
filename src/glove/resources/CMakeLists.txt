set(gc_resources_headers
    Resources.hpp
)

set(gc_resources_src
    image/Image.cc
    image/PngImage.cc

    loader/ResourceLoader.cc
)

add_library(gc_resources OBJECT ${gc_resources_src} ${gc_resources_headers})