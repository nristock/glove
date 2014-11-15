set(gc_natex_src
   SubsystemTypes.cc

   internal/DirectoryExtensionSearcher.cc
   internal/ExtensionDependencyGraph.cc
)

add_library(gc_natex STATIC ${gc_natex_src})