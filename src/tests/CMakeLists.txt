include_directories(${CMAKE_SOURCE_DIR}/vendor)

add_definitions(-DGLOVE_TESTS)

add_subdirectory(soloader)
add_subdirectory(bifrost)
add_subdirectory(graph)
add_subdirectory(pitamem)
add_subdirectory(utils)

add_custom_target(tests_all DEPENDS tests_soloader tests_graph tests_pitamem tests_utils tests_bifrost)