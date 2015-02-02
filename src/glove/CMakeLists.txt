include_directories(${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(internal)
add_subdirectory(rendering)
add_subdirectory(natex)
add_subdirectory(events)
add_subdirectory(input)
add_subdirectory(log)
add_subdirectory(graph)
add_subdirectory(filesystem)
add_subdirectory(configuration)
add_subdirectory(utils)

set(core_src
    GloveCore.cc
    GloveEnvironment.cc
    GloveException.cc

    exceptions/OperationNotSupported.cc
)

set(core_object_libs
    $<TARGET_OBJECTS:gc_rendering>
    $<TARGET_OBJECTS:gc_natex>
    $<TARGET_OBJECTS:gc_events>
    $<TARGET_OBJECTS:gc_input>
    $<TARGET_OBJECTS:gc_configuration>
    $<TARGET_OBJECTS:gc_log>
    $<TARGET_OBJECTS:gc_graph>
    $<TARGET_OBJECTS:gc_utils>
    $<TARGET_OBJECTS:gc_filesystem>
    $<TARGET_OBJECTS:glove_utils>
)

if(ON_UNIX)
    set(core_object_libs
        ${core_object_libs}
        $<TARGET_OBJECTS:gc_loaders_so>
    )
endif()

add_library(glove_core SHARED
    ${core_src}
    ${core_object_libs}
)

if(ON_UNIX)
target_link_libraries(glove_core yaml-cpp ${Boost_LIBRARIES} ${ZLIB_LIBRARY} ${PNG_LIBRARY} ${LIBZIP_LIBRARY} dl)
else()
target_link_libraries(glove_core yaml-cpp ${Boost_LIBRARIES} ${ZLIB_LIBRARY} ${PNG_LIBRARY} ${LIBZIP_LIBRARY})
endif()