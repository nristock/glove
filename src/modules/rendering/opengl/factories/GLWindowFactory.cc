#include <glove/math/IntPoint.hpp>
#include "factories/GLWindowFactory.hpp"
#include "GLWindow.hpp"

namespace BlueDwarf {
namespace gl {
std::shared_ptr<ViewportClient> GLWindowFactory::CreateViewport(const IntPoint& position, const IntPoint& size, const std::string& title) const {
    auto window = std::make_shared<GLWindow>(position, size, title);

    return std::move(window);
}
}
}