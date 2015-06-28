include_directories(${CMAKE_SOURCE_DIR})


add_executable(examples_sandbox main.cc facets/NatexFacetConfigurator.hpp facets/WindowFacet.hpp)
target_link_libraries(examples_sandbox glove)