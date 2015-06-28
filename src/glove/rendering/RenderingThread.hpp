#pragma once

#include <memory>

#include "glove/GloveApi.hpp"

namespace glove {
class Scene;

class GLOVE_API_EXPORT RenderingThread {
    std::unique_ptr<Scene> renderingScene;
};
} // namespace glove
