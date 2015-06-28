#pragma once

#include "glove/GloveApi.hpp"
#include "glove/log/Log.hpp"
#include "glove/application/GloveApplication.hpp"
#include "glove/rendering/RenderThread.hpp"

namespace glove {
/**
* The rendering core facet initializes the render dispatcher which starts the rendering thread.
*/
class GLOVE_API_EXPORT RenderingCoreFacet : public ApplicationFacet {
  public:
    RenderingCoreFacet()  : ApplicationFacet("RenderingCoreFacet") {}

    virtual void Bootstrap() override {
        L_INFO("Initializing RenderDispatcher...");
        RenderDispatcher::Initialize();
    }
};
}