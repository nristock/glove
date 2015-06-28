set(gc_application_headers

)

set(gc_application_src
    DwarfApplication.cc
)

add_library(gc_application OBJECT ${gc_application_src} ${gc_application_headers} )