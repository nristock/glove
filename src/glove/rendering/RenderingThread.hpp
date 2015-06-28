#pragma once

#include <memory>

#include "glove/BlueDwarfApi.hpp"

namespace BlueDwarf {
class Scene;

class BD_API_EXPORT RenderingThread {
    std::unique_ptr<Scene> renderingScene;
};
} // namespace BlueDwarf
