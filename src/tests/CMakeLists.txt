include_directories(${CMAKE_SOURCE_DIR}/vendor)

add_definitions(-DGLOVE_TESTS)

add_subdirectory(soloader)
add_subdirectory(bifrost)
add_subdirectory(graph)
add_subdirectory(pitamem)
add_subdirectory(rendering)
add_subdirectory(utils)
add_subdirectory(natex)
add_subdirectory(modules/glrenderer)

add_custom_target(tests_all DEPENDS tests_soloader tests_graph tests_pitamem tests_gc_rendering tests_utils tests_bifrost tests_natex)