#pragma once

#include "glove/BlueDwarfApi.hpp"
#include "glove/log/Log.hpp"
#include "glove/application/DwarfApplication.hpp"
#include "glove/rendering/RenderThread.hpp"

namespace BlueDwarf {
/**
* The rendering core facet initializes the render dispatcher which starts the rendering thread.
*/
class BD_API_EXPORT RenderingCoreFacet : public ApplicationFacet {
  public:
    RenderingCoreFacet()  : ApplicationFacet("RenderingCoreFacet") {}

    virtual void Bootstrap() override {
        L_INFO("Initializing RenderDispatcher...");
        RenderDispatcher::Initialize();
    }
};
}