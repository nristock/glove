function(add_dwarf_test test_name)
  add_test(NAME ${test_name} COMMAND ${test_name} --gtest_output=xml:${CMAKE_BINARY_DIR}/result_${test_name}.xml)
endfunction(add_dwarf_test)
