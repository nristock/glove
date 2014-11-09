add_library(vendor_gtest_main STATIC gtest.h gtest_main.cc)
target_link_libraries(vendor_gtest_main ${glove_libs})