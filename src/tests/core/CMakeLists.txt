add_executable(tests_core ConfigurationTest.cpp)
target_link_libraries(tests_core vendor_gmock vendor_gtest_main ${glove_libs})