#include <glove/natex/Natex.hpp>

#include "subsystem/GLRenderingModule.hpp"
#include "internal/GlfwWrapper.hpp"

extern "C" std::unique_ptr<glove::Module> CreateModule() {
    return std::make_unique<glove::gl::GLRenderingModule>();
}