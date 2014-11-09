if(ON_UNIX)

add_executable(tests_soloader SoLoaderTests.cpp SoLoaderFactoryTests.cpp)
target_link_libraries(tests_soloader vendor_gmock vendor_gtest_main ${glove_libs})

add_subdirectory(testlib)
add_dependencies(tests_soloader tests_soloader_testlib)

endif()