include_directories(${CMAKE_SOURCE_DIR}/vendor)

add_definitions(-DGLOVE_TESTS)

add_subdirectory(soloader)
add_subdirectory(bifrost)
add_subdirectory(graph)
add_subdirectory(rendering)
add_subdirectory(utils)
add_subdirectory(natex)
add_subdirectory(filesystem)
add_subdirectory(modules/glrenderer)
add_subdirectory(configuration)

add_custom_target(tests_all DEPENDS tests_soloader tests_graph tests_gc_rendering tests_utils tests_bifrost tests_natex tests_configuration tests_filesystem)