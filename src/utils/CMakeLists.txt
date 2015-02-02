set(glove_utils_src
   Demangle.cc
   FileUtils.cc
   RuntimePathInfo.cc
   ShaderUtils.cc
   ScreenDimensions.cc
)

add_library(glove_utils OBJECT ${glove_utils_src})