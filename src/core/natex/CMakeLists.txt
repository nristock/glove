set(gc_natex_src
   BifrostLoader.cc
   GloveSubsystemDefinition.cc
   GloveSubsystemDefinitionRegistry.cc
   GloveSubsystemInstanceRegistry.cc
   DirectoryExtensionSearcher.cc

   internal/ExtensionDependencyGraph.cc
)

add_library(gc_natex OBJECT ${gc_natex_src})