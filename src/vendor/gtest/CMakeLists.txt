include_directories("${PROJECT_ROOT}/src")

add_library(vendor_gtest_main STATIC gtest.hpp gtest_main.cc)
target_link_libraries(vendor_gtest_main)