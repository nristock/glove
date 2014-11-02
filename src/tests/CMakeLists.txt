include_directories(${CMAKE_SOURCE_DIR}/vendor)

add_subdirectory(core)
add_subdirectory(graph)
add_subdirectory(pitamem)
add_subdirectory(utils)

add_custom_target(tests_all DEPENDS tests_core tests_graph tests_pitamem tests_utils)