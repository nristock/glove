#include <glove/natex/Natex.hpp>

#include "subsystem/GLRenderingModule.hpp"
#include "internal/GlfwWrapper.hpp"

extern "C" std::unique_ptr<BlueDwarf::Module> CreateModule() {
    return std::make_unique<BlueDwarf::gl::GLRenderingModule>();
}