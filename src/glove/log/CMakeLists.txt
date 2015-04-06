set(gc_log_src
   Logger.cc
   Message.cc
   format.cc
)

set(gc_log_headers
    Log.hpp

    MessageProcessor.hpp
    MessageProcessors.hpp

    processors/AsyncProcessor.hpp
    processors/ConsoleOutProcessor.hpp
    processors/DefaultFormatterProcessor.hpp
)

add_library(gc_log OBJECT ${gc_log_src} ${gc_log_headers})