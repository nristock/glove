set(gc_natex_src
   SubsystemTypes.cc
   BifrostLoader.cc
   GloveSubsystemDefinition.cc
   GloveSubsystemDefinitionRegistry.cc
   GloveSubsystemInstanceRegistry.cc
   DirectoryExtensionSearcher.cc

   internal/ExtensionDependencyGraph.cc
)

add_library(gc_natex STATIC ${gc_natex_src})