add_executable(tests_graph mock/GameObjectMock.h ScenegraphTest.cc TransformTest.cc)
target_link_libraries(tests_graph vendor_gmock vendor_gtest_main ${glove_libs})