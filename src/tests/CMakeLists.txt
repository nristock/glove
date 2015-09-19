include_directories(${CMAKE_SOURCE_DIR}/vendor ${CMAKE_SOURCE_DIR})

add_definitions(-DGLOVE_TESTS)

add_subdirectory(application)
add_subdirectory(utils)
add_subdirectory(natex)
add_subdirectory(filesystem)
add_subdirectory(configuration)
add_subdirectory(resources)
add_subdirectory(services)
add_subdirectory(input)
add_subdirectory(events)
add_subdirectory(world)
add_subdirectory(threading)
add_subdirectory(log)
add_subdirectory(mock)

add_custom_target(tests_unit DEPENDS tests_log tests_application tests_events tests_threading tests_world tests_input tests_services tests_utils tests_natex tests_configuration tests_filesystem tests_resources)