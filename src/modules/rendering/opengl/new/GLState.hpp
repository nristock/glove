#pragma once

#include <array>

#include <glove/CommonTypes.hpp>
#include <glove/math/IntRect.hpp>

#include "GLTexture.hpp"
#include "../internal/OpenGLWrapper.hpp"

namespace BlueDwarf {
namespace gl {

struct OpenGLContextState {
    GLuint framebuffer;
    std::array<GLuint, 1> renderTargets;
    GLuint depthStencilTarget = 0;

    std::array<GLuint, 1> textures;

    bool enableScissor;
    IntRect scissor;
    IntRect viewport;

    bool enableDepthTest;
    bool enableStencilTest;

    GLuint vao;
    GLuint shaderProgram;
};
}
}
