set(gc_configuration_src
    Configuration.cc
)

set(gc_configuration_headers
    Configuration.hpp
    ConfigurationConverters.hpp
)

add_library(gc_configuration OBJECT ${gc_configuration_src} ${gc_configuration_headers})