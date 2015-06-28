#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glove/rendering/SceneView.hpp>
#include <glove/world/Transform.hpp>
#include <glove/GloveException.hpp>

#include "GLWindow.hpp"
#include "internal/GlfwWrapper.hpp"

GLEWContext* glewGetContext();

namespace glove {
namespace gl {

GLWindow::GLWindow(const IntPoint& position, const IntPoint& size, const std::string& title) {
    glfwWindow = GlfwWrapper::CreateGlfwWindow(position, size, title, this);
    glewContext = new GLEWContext();

    MakeCurrent();

    glewExperimental = GL_TRUE;
    GLenum glewInitRes = glewInit();
    if (glewInitRes != GLEW_OK) {
        throw GLOVE_EXCEPTION(std::string((char*)glewGetErrorString(glewInitRes)));
    }
}

GLWindow::~GLWindow() {
    glfwDestroyWindow(glfwWindow);
}

void GLWindow::MakeCurrent() {
    glfwMakeContextCurrent(glfwWindow);
}

void GLWindow::SwapBuffers() {
    glfwSwapBuffers(glfwWindow);
}

void GLWindow::OnKeyEvent(int key, int scancode, int action, int mods) {
    const Key& gloveKey = GlfwWrapper::ConvertKeyCode(key);
    KeyState newState(action == GLFW_PRESS);

    gloveKey.UpdateState(newState);
}

void GLWindow::OnMouseMove(double x, double y) {
    static double oldX = x;
    static double oldY = y;

    double deltaX = x - oldX;
    double deltaY = y - oldY;

    if(std::abs(deltaX) > 0.01f) {
        KeyState newState(static_cast<float>(x));
        Keys::MouseX.UpdateState(newState);
    }

    if(std::abs(deltaY) > 0.01f) {
        KeyState newState(static_cast<float>(y));
        Keys::MouseY.UpdateState(newState);
    }
}

void GLWindow::OnMouseButton(int button, int action, int mods) {
    const Key& gloveKey = GlfwWrapper::ConvertKeyCode(button);
    KeyState newState(action == GLFW_PRESS);

    gloveKey.UpdateState(newState);
}

std::string GLWindow::GetContextVersion() const {
    return (boost::format("OpenGL %1%.%2%.%3%") % glfwGetWindowAttrib(glfwWindow, GLFW_CONTEXT_VERSION_MAJOR) %
            glfwGetWindowAttrib(glfwWindow, GLFW_CONTEXT_VERSION_MINOR) %
            glfwGetWindowAttrib(glfwWindow, GLFW_CONTEXT_REVISION)).str();
}

GLFWwindow* GLWindow::GetGlfwWindow() const {
    return glfwWindow;
}

GLEWContext* GLWindow::GetGlewContext() const {
    return glewContext;
}


void GLWindow::PollSystemEvents() {
    glfwPollEvents();
}

bool GLWindow::ShouldClose() {
    return glfwWindowShouldClose(glfwWindow) != 0;
}

IntPoint GLWindow::GetClientArea() const {
    int width, height;
    glfwGetFramebufferSize(glfwWindow, &width, &height);

    return {width, height};
}

void GLWindow::Flush(const RenderTarget& renderTarget) {

}

void GLWindow::GLFlush(const RenderTarget& renderTarget, GLRenderHardwareInterface& renderHardwareInterface) {
    auto clientArea = GetClientArea();
    renderHardwareInterface.BlitToDefaultFramebuffer(renderTarget, clientArea.x, clientArea.y);
    SwapBuffers();
}
}
} // namespace glove

GLEWContext* glewGetContext() {
    return glove::gl::GlfwWrapper::GetCurrentGLWindow()->GetGlewContext();
}