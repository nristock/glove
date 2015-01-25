add_executable(tests_gc_rendering
    VertexAttributeUtilsTest.cc
    WindowConstructionHintsTest.cc
    MeshTest.cc
    IndexDataTest.cc
    VertexDataTest.cc
    VertexLayoutTest.cc
    VertexAttributeTest.cc
    RendererBaseTest.cc
    OrthoCameraTest.cc
    CameraBaseTest.cc
)
target_link_libraries(tests_gc_rendering vendor_gmock vendor_gtest_main ${glove_libs})