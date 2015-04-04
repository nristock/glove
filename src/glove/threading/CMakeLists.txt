set(gc_threading_headers

)

set(gc_threading_src
   Thread.cc
   TaskQueue.cc
   ThreadPool.cc
   Async.cc
)

add_library(gc_threading OBJECT ${gc_threading_src} ${gc_threading_headers})