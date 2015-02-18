if(ON_UNIX)

add_executable(tests_services GloveServiceRegistryTest.cc)
target_link_libraries(tests_services vendor_gmock vendor_gtest_main glove)

endif()