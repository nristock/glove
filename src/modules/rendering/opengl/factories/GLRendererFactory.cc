#include "factories/GLRendererFactory.hpp"
#include "GLRenderer.hpp"

namespace glove {
namespace gl {

GLRendererFactory::GLRendererFactory() : nextContextId(0) {
}

IRendererPtr GLRendererFactory::CreateRenderer(const WindowConstructionHints& windowDescription) {
    return GLRendererPtr(new GLRenderer(windowDescription, nextContextId++),
                         [=](GLRenderer* ptr) { delete ptr; });
}
}
}