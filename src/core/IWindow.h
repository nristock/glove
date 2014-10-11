#pragma once

#include <string>

#include <glm/glm.hpp>

#include "core/GloveFwd.h"

namespace glove {

class IWindow {
public:
    virtual void MakeCurrent() = 0;
    virtual void SetFramebuffer(int newWidth, int newHeight) = 0;

    virtual void SwapBuffers() = 0;

    virtual bool CloseRequested() const = 0;

    virtual std::string GetContextVersion() const = 0;

    virtual glm::mat4 GetProjMatrix() const = 0;
};

} /* namespace glove */