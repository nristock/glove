#pragma once

#include <glove/rendering/WindowFactoryService.hpp>

namespace BlueDwarf {
namespace gl {
class GLWindowFactory : public WindowFactoryService {
  public:
    std::shared_ptr<ViewportClient> CreateViewport(const IntPoint& position, const IntPoint& size,
                                                        const std::string& title) const;
};
}
} /* namespace BlueDwarf */