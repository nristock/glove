add_executable(tests_graph mock/GameObjectMock.h mock/MockGameObjectFactory.cc ScenegraphTest.cc TransformTest.cc)
target_link_libraries(tests_graph vendor_gmock vendor_gtest_main glove m)