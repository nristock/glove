include_directories(${CMAKE_SOURCE_DIR}/modules/rendering/opengl)

add_executable(tests_mod_glrenderer
    GLRendererSubsystemDefinitionTest.cc
    GLRendererSubsystemTest.cc
    GLRendererExtensionTest.cc
)
target_link_libraries(tests_mod_glrenderer vendor_gmock vendor_gtest_main ${glove_libs} mod_glrenderer)