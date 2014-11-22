add_subdirectory(internal)
add_subdirectory(rendering)
add_subdirectory(natex)
add_subdirectory(events)
add_subdirectory(input)
add_subdirectory(log)
add_subdirectory(graph)
add_subdirectory(pitamem)

set(core_src
    Configuration.cc
    GloveCore.cc
    GloveEnvironment.cc
    GloveException.cc
    GlovePlugin.cc
    PluginLoader.cc
)

add_library(glove_core ${core_src})
target_link_libraries(glove_core gc_rendering gc_natex gc_events gc_input gc_log gc_graph gc_pitamem)

if(ON_UINX)
target_link_libraries(glove_core gc_loaders_so)
endif()