#pragma once

#include <memory>

#include <glove/rendering/RendererService.hpp>
#include "new/GLRenderHardwareInterface.hpp"

namespace glove {
namespace gl {

class GLRendererService : public RendererService {
  public:
    GLRendererService() : rhi(new GLRenderHardwareInterface()) {}

    virtual std::shared_ptr<RenderHardwareInterface> GetRenderHardwareInterface() const override { return rhi; }

  private:
    std::shared_ptr<GLRenderHardwareInterface> rhi;
};
}
}