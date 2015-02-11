set(gc_natex_headers
    IExtensionSearcher.hpp
    ISharedLibraryLoader.hpp
    ISharedLibraryLoaderFactory.hpp
    ISubsystem.hpp
    ISubsystemDefinition.hpp
    ISubsystemDefinitionRegistry.hpp
    ISubsystemFactory.hpp
    ISubsystemInstanceRegistry.hpp
    ISystemExtension.hpp
    ISystemExtensionLoader.hpp
    Natex.hpp
)

set(gc_natex_src
   BifrostLoader.cc
   GloveSubsystemDefinition.cc
   GloveSubsystemDefinitionRegistry.cc
   GloveSubsystemInstanceRegistry.cc
   DirectoryExtensionSearcher.cc

   internal/ExtensionDependencyGraph.cc
)

add_library(gc_natex OBJECT ${gc_natex_src} ${gc_natex_headers})