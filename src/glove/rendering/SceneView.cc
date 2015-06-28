#include "glove/rendering/SceneView.hpp"
#include "glove/world/scene/SceneProxy.hpp"

namespace glove {

void SceneViewComposition::CalculateFamilySize() {
    compositionWidth = 0;
    compositionHeight = 0;

    for(auto& view : views) {
        const ViewRect& rect = view.GetViewRect();
        uint32 rectBottom = rect.GetY() + rect.GetHeight();
        uint32 rectRight = rect.GetX() + rect.GetWidth();

        compositionHeight = (rectBottom > compositionHeight) ? rectBottom : compositionHeight;
        compositionWidth = (rectRight > compositionWidth) ? rectRight : compositionWidth;
    }
}
} /* namespace glove */