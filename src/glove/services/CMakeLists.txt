set(gc_services_headers
    Services.hpp

    Service.hpp
    ServiceRegistry.hpp

    exceptions/ServiceNotFound.hpp
    exceptions/ServiceNotInitialized.hpp
)

set(gc_services_src
    impl/GloveServiceRegistry.cc
)

add_definitions(-DGLOVE_SERVICES_FWD_ONLY)
add_library(gc_services OBJECT ${gc_services_src} ${gc_services_headers})