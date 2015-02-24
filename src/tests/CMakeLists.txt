include_directories(${CMAKE_SOURCE_DIR}/vendor ${CMAKE_SOURCE_DIR})

add_definitions(-DGLOVE_TESTS)

add_subdirectory(bifrost)
add_subdirectory(graph)
add_subdirectory(rendering)
add_subdirectory(utils)
add_subdirectory(natex)
add_subdirectory(filesystem)
add_subdirectory(modules/glrenderer)
add_subdirectory(configuration)
add_subdirectory(resources)
add_subdirectory(services)
add_subdirectory(input)
add_subdirectory(events)

add_custom_target(tests_unit DEPENDS tests_events tests_input tests_services tests_graph tests_gc_rendering tests_utils tests_bifrost tests_natex tests_configuration tests_filesystem tests_resources)

add_test(NAME CORE_Events COMMAND tests_events)
add_test(NAME CORE_Input COMMAND tests_input)
add_test(NAME CORE_Services COMMAND tests_services)