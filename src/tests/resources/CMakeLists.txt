add_executable(tests_resources PngImageTest.cc)
target_link_libraries(tests_resources vendor_gmock vendor_gtest_main glove m)

add_custom_command(TARGET tests_resources POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/tests/resources/testdata"
        $<TARGET_FILE_DIR:tests_resources>/testdata)

add_dwarf_test(tests_resources)