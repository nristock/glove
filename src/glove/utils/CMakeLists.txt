set(gc_utils_headers
   IsA.hpp
   TypeInfo.hpp
)

set(gc_utils_src
   BitMask.cc
   FileUtils.cc
   RuntimePathInfo.cc
   ScreenDimensions.cc
   ShaderUtils.cc
)

add_library(gc_utils OBJECT ${gc_utils_src} ${gc_utils_headers})