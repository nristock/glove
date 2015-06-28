#pragma once

#include "glove/GloveApi.hpp"
#include "glove/services/BasicService.hpp"
#include "glove/math/IntRect.hpp"

namespace glove {
class ViewportClient;


/**
* This factory service is responsible for building windows to which a World can be rendered.
*/
class GLOVE_API_EXPORT WindowFactoryService : public BasicService {
  public:
    static ServiceType Type;

    WindowFactoryService() : BasicService(Type) {}

    virtual std::shared_ptr<ViewportClient> CreateViewport(const IntPoint& position, const IntPoint& size,
                                                        const std::string& title) const = 0;
};

struct GLOVE_API_EXPORT WindowBuilder {
  public:
    WindowBuilder& SetPosition(IntPoint position) {
        this->position = position;
        return *this;
    }

    WindowBuilder& SetSize(IntPoint dimensions) {
        this->size = dimensions;
        return *this;
    }

    WindowBuilder& SetTitle(const std::string& title) {
        this->title = title;
        return *this;
    }

    std::shared_ptr<ViewportClient> Finalize(const WindowFactoryService& windowFactory) {
        return std::move(windowFactory.CreateViewport(position, size, title));
    }

  private:
    IntPoint position;
    IntPoint size;
    std::string title;
};
} // namespace glove
