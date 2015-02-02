set(gci_so_src
   SoLoader.cc
   SoLoaderFactory.cc
)

add_library(gc_loaders_so OBJECT ${gci_so_src})
#target_link_libraries(gc_loaders_so dl)