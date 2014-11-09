add_executable(tests_utils StringIdDatabaseTest.cc StringIdTest.cc)
target_link_libraries(tests_utils vendor_gmock vendor_gtest_main ${glove_libs})