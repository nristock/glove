set(opengl_renderer_src
    GLRenderer.cc
    GLWindow.cc
)

add_library(opengl_renderer SHARED ${opengl_renderer_src})