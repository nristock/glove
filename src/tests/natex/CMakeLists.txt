add_executable(tests_natex DirectoryExtensionSearcherTests.cc ExtensionDependencyGraphTests.cc)
target_link_libraries(tests_natex vendor_gmock vendor_gtest_main ${glove_libs})

add_custom_command(TARGET tests_natex POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/tests/natex/testdata"
        $<TARGET_FILE_DIR:tests_natex>/testdata)