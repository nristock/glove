add_executable(tests_input
    KeyTest.cc
    KeyStateChangedTest.cc
)
target_link_libraries(tests_input vendor_gmock vendor_gtest_main glove)