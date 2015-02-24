set(gc_natex_headers
    ExtensionSearcher.hpp
    ModuleLoader.hpp
    Natex.hpp

    SharedLibrary.hpp
    SharedLibraryLoader.hpp

    exceptions/SharedLibraryLoadFailed.hpp
    exceptions/SymbolNotFound.hpp
)

set(gc_natex_src
   BifrostLoader.cc
   DirectoryExtensionSearcher.cc
   Module.cc
   BasicModule.cc

   impl/UnixSharedLibrary.cc
   impl/GloveSharedLibraryLoader.cc
   impl/SharedLibraryModule.cc
)

add_definitions(-DGLOVE_NATEX_FWD_ONLY)
add_library(gc_natex OBJECT ${gc_natex_src} ${gc_natex_headers})