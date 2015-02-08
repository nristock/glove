add_executable(tests_filesystem
    NativeFilesystemAccessorsTest.cc
    UnbufferedFileReaderTest.cc
    PathTest.cc
    FileTest.cc
    ZipArchiveTest.cc
    ZipEntryBufferTest.cc
    ZipFilesystemTest.cc
)
target_link_libraries(tests_filesystem vendor_gmock vendor_gtest_main glove)

add_custom_command(TARGET tests_filesystem POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/tests/filesystem/testdata"
        $<TARGET_FILE_DIR:tests_filesystem>/testdata)