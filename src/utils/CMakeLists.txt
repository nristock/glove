set(glove_utils_src
   Demangle.cc
   FileUtils.cc
   RuntimePathInfo.cc
   ShaderUtils.cc
   StringId.cc
   StringIdDatabase.cc
)

add_library(glove_utils OBJECT ${glove_utils_src})