add_executable(tests_events
    EventDelegateTest.cc
)
target_link_libraries(tests_events vendor_gmock vendor_gtest_main glove)